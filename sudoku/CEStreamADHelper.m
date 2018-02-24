//
//  CEStreamADHelper.m
//  Pods
//
//
//

#import "CEStreamADHelper.h"
#import "I2WAPI+Deprecated.h"
#import "CEAdView.h"

#pragma mark - ADHolder
@implementation CEADHolder
- (instancetype) initWithAdView:(ADView *)adView section:(NSUInteger)section row:(NSUInteger)row {
    self = [super init];

    if (self) {
        _adView = adView;
        _isShowing = NO;
        _isPlaying = NO;
        _section = section;
        _row = row;
    }

    return self;
}

@end

#pragma mark - CEStreamPositionManager
@implementation CEStreamPositionManager

- (instancetype) initWithPlacement:(NSString *)placement minPos:(int)minPos maxPos:(int)maxPos {
    self = [super init];

    if (self) {
        _placement = placement;
        _tag = nil;
        _minPos = minPos;
        _maxPos = maxPos;
        _servingFreq = [I2WAPI getStreamADServingFreqWithPlacement:placement];
    }

    return self;
}

- (instancetype) initWithTag:(NSString *)tag minPos:(int)minPos maxPos:(int)maxPos {
    self = [super init];

    if (self) {
        _placement = nil;
        _tag = tag;
        _minPos = minPos;
        _maxPos = maxPos;
        _servingFreq = [I2WAPI getStreamADServingFreqWithPlacement:nil];
    }

    return self;
}

@end

#pragma mark - CEStreamADHelper
@interface CEStreamADHelper ()
@property (nonatomic, assign) int place;
@property (nonatomic, assign) float adWidth;
@property (nonatomic, strong) NSMutableArray * prohibitPositions;

// serving conf
@property (nonatomic, assign) int firstVisiblePosition;
@property (nonatomic, assign) int lastVisiblePosition;

// state
@property (nonatomic, assign) BOOL isActive;
@property (nonatomic, assign) BOOL enableAutoPlay;
@property (nonatomic, assign) BOOL enableVideoAutoReplay;
@property (nonatomic, strong) NSString * token;
@end

@implementation CEStreamADHelper

#pragma mark - constructor
- (instancetype) initWithDelegate:(id<CEStreamAdHelperDelegate>)delegate {
    self = [super init];

    if (self) {
        _delegate = delegate;
        _adHolders = [[NSMutableDictionary alloc] init];

        _key = nil;
        _place = 1;
        _adWidth = -1;

        _firstVisiblePosition = -1;
        _lastVisiblePosition = -1;

        // state
        _isActive = NO;
        _enableAutoPlay = YES;
        _enableVideoAutoReplay = YES;
        _curPlacement = nil;
        _lastViewedPosition = -1;
        _reqTimeout = 5.0;

        _prohibitPositions = [[NSMutableArray alloc] init];
        _desiredPositions = [[NSMutableArray alloc] init];
        _placementAdViewRecycled = [[NSMutableDictionary<NSString *, ADView *> alloc] init];
        _isPlacementProcessing = [[NSMutableDictionary<NSString *, NSNumber *> alloc] init];
        _placementLastAddedPosition = [[NSMutableDictionary<NSString *, NSNumber *> alloc] init];
    }

    return self;
} /* initWithDelegate */

#pragma mark - public API
- (void) setAdWidth:(float)width {
    if (width > 0) {
        _adWidth = width;
    }
}

- (void) setActive:(BOOL)isActive {
    _isActive = isActive;

    if (isActive) {
        [I2WAPI setActivePlacements:_channelPlacements];
    }

    [self updateAdStatus];
}

- (NSUInteger) adjustedNumberOfItems:(NSUInteger)numberOfItems inSection:(NSUInteger)section {
    if (numberOfItems <= 0) {
        return 0;
    }

    NSIndexPath * pathOfLastItem = [NSIndexPath indexPathForRow:numberOfItems inSection:section];
    NSUInteger numberOfAdsBeforeLastItem = [self findAdCountInSameSectionBeforeOriginIndexPath:pathOfLastItem];

    return numberOfItems + numberOfAdsBeforeLastItem;
}

- (void) prerollWithVisibleCounts:(int)visibleCounts {
    NSLog(@"CEStreamADHelper Error: should not called parent method");
}

- (void) prerollWithStartPosition:(int)startPosition endPosition:(int)endPosition {
    NSLog(@"CEStreamADHelper Error: should not called parent method");
}

- (void) reset {
    // clean all previous ads
    _place = 1;

    for (NSNumber * posNum in _adHolders) {
        CEADHolder * holder = [_adHolders objectForKey:posNum];
        [[holder adView] removeFromSuperview];
        [[holder adView] onHide];
        [[holder adView] onStop];
    }

    _adHolders = [[NSMutableDictionary alloc] init];
    _curPlacement = nil;
    // A trick so we can pass the initial condition and insert ad at the minimum position!
    _firstVisiblePosition = -1;
    _lastVisiblePosition = -1;
    _lastViewedPosition = -1;

    [_prohibitPositions removeAllObjects];
    [_desiredPositions removeAllObjects];
    [_placementLastAddedPosition removeAllObjects];
} /* reset */

- (void) setAppAdsIndexPaths:(NSArray *)appAdsIndexPaths {
    [_prohibitPositions removeAllObjects];
    NSArray * adjustedIndexPaths = [self adjustedIndexPathsForOriginalIndexPaths:appAdsIndexPaths];

    for (NSIndexPath * adjustedIndexPath in adjustedIndexPaths) {
        int adjustedPos = [_delegate indexPathToPosition:adjustedIndexPath];

        if ([_prohibitPositions containsObject:@(adjustedPos)] == NO) {
            [_prohibitPositions addObject:@(adjustedPos)];
        }

        if ([_prohibitPositions containsObject:@(adjustedPos + 1)] == NO) {
            [_prohibitPositions addObject:@(adjustedPos + 1)];
        }
    }
}

- (void) setAdCustomIndexPaths:(NSArray *)adIndexPaths {
    [_desiredPositions removeAllObjects];
    adIndexPaths = [adIndexPaths sortedArrayUsingSelector:@selector(compare:)];
    NSArray * adjustedIndexPaths = [self adjustedIndexPathsForOriginalIndexPaths:adIndexPaths];

    for (NSIndexPath * adjustedIndexPath in adjustedIndexPaths) {
        int adjustedPos = [_delegate indexPathToPosition:adjustedIndexPath];

        if ([_desiredPositions containsObject:@(adjustedPos)] == NO) {
            [_desiredPositions addObject:@(adjustedPos)];
        }
    }
}

- (void) setAutoPlay:(BOOL)enableAutoPlay {
    _enableAutoPlay = enableAutoPlay;
}

- (void) setAutoReplay:(BOOL)enableAutoReplay {
    _enableVideoAutoReplay = enableAutoReplay;
}

- (void) startAdAtPosition:(NSUInteger)position {
    if ([_adHolders objectForKey:@(position)]) {
        CEADHolder * holder = [_adHolders objectForKey:@(position)];
        [holder.adView onStart];
        holder.isPlaying = YES;
    }
}

- (void) stopAdAtPosition:(NSUInteger)position {
    if ([_adHolders objectForKey:@(position)]) {
        CEADHolder * holder = [_adHolders objectForKey:@(position)];
        [holder.adView onStop];
        holder.isPlaying = NO;
    }
}

- (UIView *) loadAdAtIndexPath:(NSIndexPath *)indexPath {
    NSLog(@"CEStreamADHelper Error: should not called parent method");
    return nil;
}

- (BOOL) isAdAtIndexPath:(NSIndexPath *)indexPath {
    int pos = [_delegate indexPathToPosition:indexPath];

    return [_adHolders objectForKey:@(pos)] != nil;
}

- (CGSize) getAdSizeAtIndexPath:(NSIndexPath *)indexPath {
    if (![self isAdAtIndexPath:indexPath]) {
        return CGSizeZero;
    }

    int pos = [_delegate indexPathToPosition:indexPath];
    CEADHolder * holder = [_adHolders objectForKey:@(pos)];
    return [holder adView].bounds.size;
}

- (NSIndexPath *) originalIndexPathForAdjustedIndexPath:(NSIndexPath *)indexPath {
    if (!indexPath || indexPath.row == NSNotFound) {
        return indexPath;
    } else if ([self isAdAtIndexPath:indexPath]) {
        return nil;
    } else {
        NSUInteger numberOfAdsBeforeIndexPath = [self findAdCountInSameSectionBeforeAdjustedIndexPath:indexPath];
        return [NSIndexPath indexPathForRow:indexPath.row - numberOfAdsBeforeIndexPath inSection:indexPath.section];
    }
}

- (NSIndexPath *) adjustedIndexPathForOriginalIndexPath:(NSIndexPath *)indexPath {
    if (!indexPath || indexPath.row == NSNotFound) {
        return indexPath;
    }

    NSUInteger numberOfAdsBeforeIndexPath = [self findAdCountInSameSectionBeforeOriginIndexPath:indexPath];
    return [NSIndexPath indexPathForRow:indexPath.row + numberOfAdsBeforeIndexPath inSection:indexPath.section];
}

- (NSArray *) originalIndexPathsForAdjustedIndexPaths:(NSArray *)indexPaths {
    NSMutableArray * originalIndexPaths = [NSMutableArray array];

    for (NSIndexPath * indexPath in indexPaths) {
        NSIndexPath * originalIndexPath = [self originalIndexPathForAdjustedIndexPath:indexPath];

        if (originalIndexPath) {
            [originalIndexPaths addObject:originalIndexPath];
        }
    }

    return [originalIndexPaths copy];
}

- (NSArray *) adjustedIndexPathsForOriginalIndexPaths:(NSArray *)indexPaths {
    NSMutableArray * adjustedIndexPaths = [NSMutableArray array];

    for (NSIndexPath * indexPath in indexPaths) {
        [adjustedIndexPaths addObject:[self adjustedIndexPathForOriginalIndexPath:indexPath]];
    }

    return [adjustedIndexPaths copy];
}

- (void) insertItemsAtIndexPaths:(NSArray *)originalIndexPaths {
    originalIndexPaths = [originalIndexPaths sortedArrayUsingSelector:@selector(compare:)];

    for (NSIndexPath * oriIndexPath in originalIndexPaths) {
        NSIndexPath * adjustedIndexPath = [self adjustedIndexPathForOriginalIndexPath:oriIndexPath];
        NSArray * keys = [_adHolders allKeys];

        for (NSNumber * adPos in keys) {
            CEADHolder * holder = [_adHolders objectForKey:adPos];

            if (holder.section != adjustedIndexPath.section) {
                continue;
            }

            if (holder.row >= adjustedIndexPath.row) {
                int newPos = [adPos intValue] + 1;
                [_adHolders removeObjectForKey:adPos];
                [_adHolders setObject:holder forKey:@(newPos)];
            }
        }
    }
} /* insertItemsAtIndexPaths */

- (void) deleteItemsAtIndexPaths:(NSArray *)originalIndexPaths {
    originalIndexPaths = [originalIndexPaths sortedArrayUsingSelector:@selector(compare:)];

    for (NSIndexPath * oriIndexPath in originalIndexPaths) {
        NSIndexPath * adjustedIndexPath = [self adjustedIndexPathForOriginalIndexPath:oriIndexPath];

        if ([self isAdAtIndexPath:adjustedIndexPath]) {
            [_adHolders removeObjectForKey:adjustedIndexPath];
        }
    }
}

- (void) moveItemAtIndexPath:(NSIndexPath *)fromIndexPath toIndexPath:(NSIndexPath *)toIndexPath {
}

- (void) insertSections:(NSIndexSet *)sections {
    [sections enumerateIndexesUsingBlock:^(NSUInteger idx, BOOL * stop) {
         NSArray * keys = [_adHolders allKeys];

         for (NSNumber * adPos in keys) {
             CEADHolder * holder = [_adHolders objectForKey:adPos];

             if (holder.section >= idx) {
                 holder.section++;
             }
         }
     }];
}

- (void) deleteSections:(NSIndexSet *)sections {
    [sections enumerateIndexesUsingBlock:^(NSUInteger idx, BOOL * stop) {
         NSArray * keys = [_adHolders allKeys];

         for (NSNumber * adPos in keys) {
             CEADHolder * holder = [_adHolders objectForKey:adPos];

             if (holder.section == idx) {
                 [_adHolders removeObjectForKey:adPos];
             }
         }
     }];
}

- (void) moveSection:(NSInteger)section toSection:(NSInteger)newSection {
    NSArray * keys = [_adHolders allKeys];

    for (NSNumber * adPos in keys) {
        CEADHolder * holder = [_adHolders objectForKey:adPos];

        if (holder.section == section) {
            NSIndexPath * newIndexPath = [NSIndexPath indexPathForRow:holder.row inSection:newSection];
            holder.section = newSection;
            [_adHolders removeObjectForKey:adPos];
            int newPos = [_delegate indexPathToPosition:newIndexPath];
            [_adHolders setObject:holder forKey:@(newPos)];
        }
    }
}

- (void) updateVisibleCellsFromPosition:(int)firstPos toPosition:(int)lastPos {
    _firstVisiblePosition = firstPos;
    _lastVisiblePosition = lastPos;

    _lastViewedPosition = MAX(_lastVisiblePosition, _lastViewedPosition);

    // for ad status onShow/onHide event
    [self updateAdStatus];
}

- (void) requestAdWithPlacement:(NSString *)placement {
    [self requestAdWithPlacement:placement isPreroll:NO];
}

- (void) requestAdWithPlacement:(NSString *)placement isPreroll:(BOOL)isPreroll {
    void (^ onReady)(ADView *) = ^(ADView * adView) {
        
        SEL mySelector = NSSelectorFromString(@"setReplayMode:");
        NSMethodSignature* signature1 = [adView methodSignatureForSelector:mySelector];
        if (signature1) {
            NSInvocation *invocation = [NSInvocation invocationWithMethodSignature:signature1];
            [invocation setTarget:adView];
            [invocation setSelector:mySelector];
            NSUInteger mode = _enableVideoAutoReplay ? 1 : 0;
            [invocation setArgument:&mode atIndex:2];
            [invocation invoke];
        }
   
        if (placement == self.curPlacement) {
            [self onADLoaded:adView
                   placement:placement
                   isPreroll:isPreroll];
        } else {
            [self.placementAdViewRecycled setObject:adView forKey:placement];
        }

        [self.isPlacementProcessing setObject:[NSNumber numberWithBool:NO] forKey:placement];
    };

    ADView * recycledAdViewInPlacement = [self.placementAdViewRecycled objectForKey:placement];

    if (recycledAdViewInPlacement) {
        [self.placementAdViewRecycled removeObjectForKey:placement];
        onReady(recycledAdViewInPlacement);
        return;
    }

    __weak typeof(_delegate) weakDelegate = _delegate;

    [I2WAPI getStreamADWithPlacement:placement
                           helperKey:_key
                               place:_place
                             adWidth:_adWidth
                             timeout:isPreroll ? 0 : self.reqTimeout
                             onReady:onReady
                           onFailure:^(NSError * error) {
         [self.isPlacementProcessing
          setObject:[NSNumber numberWithBool:NO]
             forKey:placement];
     }
                 onPullDownAnimation:^(UIView * adView) {
         [weakDelegate CEStreamADOnPulldownAnimation];
     }
    ];
} /* requestAdWithPlacement */

#pragma mark - private method
- (void) updateProhibitPosWithAdPos:(int)adPos {
    NSMutableArray * newProhitbitPos = [[NSMutableArray alloc] init];

    for (NSNumber * prohibitPos in _prohibitPositions) {
        if ([prohibitPos intValue] >= adPos) {
            [newProhitbitPos addObject:@([prohibitPos intValue] + 1)];
        } else {
            [newProhitbitPos addObject:prohibitPos];
        }
    }

    _prohibitPositions = newProhitbitPos;
}

#pragma mark - indexPath helper
- (NSUInteger) findAdCountInSameSectionBeforeAdjustedIndexPath:(NSIndexPath *)indexPath {
    NSUInteger count = 0;

    for (NSNumber * adPos in [_adHolders allKeys]) {
        CEADHolder * holder = [_adHolders objectForKey:adPos];

        if (holder.section != indexPath.section) {
            continue;
        }

        if (holder.row <= indexPath.row) {
            count++;
        }
    }

    return count;
}

- (NSUInteger) findAdCountInSameSectionBeforeOriginIndexPath:(NSIndexPath *)indexPath {
    NSUInteger count = 0;
    NSUInteger oriRow = indexPath.row;

    NSArray * keys = [_adHolders allKeys];

    keys = [keys sortedArrayUsingSelector:@selector(compare:)];

    for (NSNumber * adPos in keys) {
        CEADHolder * holder = [_adHolders objectForKey:adPos];

        if (holder.section != indexPath.section) {
            continue;
        }

        if (holder.row <= oriRow) {
            oriRow++;
            count++;
        }
    }

    return count;
} /* findAdCountInSameSectionBeforeOriginIndexPath */

- (void) onADLoaded:(ADView *)adView placement:(NSString *)placement isPreroll:(BOOL)isPreroll {
    int targetPosIndex = -1;
    if ([_desiredPositions count] == 0) {
        targetPosIndex = self.lastViewedPosition + 1;
        NSNumber *lastAdPosition = self.placementLastAddedPosition[placement];
        if (lastAdPosition) {
            targetPosIndex = MAX(targetPosIndex, lastAdPosition.intValue + self.positionMgr.servingFreq);
        }
        while ([_prohibitPositions containsObject:@(targetPosIndex)])
            targetPosIndex++;
    } else {
        NSArray * curDesiredPositions = [_desiredPositions copy];

        for (NSNumber * desiredPos in curDesiredPositions) {
            // this position already has ad
            if ([_adHolders objectForKey:desiredPos] != nil) {
                continue;
            }

            if ([desiredPos intValue] >= _lastVisiblePosition + 1) {
                targetPosIndex = [desiredPos intValue];
                break;
            }
        }
    }

    if (targetPosIndex != -1 && adView != nil) {
        NSIndexPath * targetIndexPath = [_delegate positionToIndexPath:targetPosIndex];

        if (targetIndexPath == nil) {
            [self.placementAdViewRecycled setObject:adView forKey:placement];
            return;
        }

        NSLog(@"insert ad at position: %d, is preroll: %d", targetPosIndex, isPreroll);
        CEADHolder * newADHolder = [[CEADHolder alloc] initWithAdView:adView section:targetIndexPath.section row:targetIndexPath.row];
        [_adHolders setObject:newADHolder forKey:@(targetPosIndex)];

        BOOL viewDidInserted = YES;

        if (isPreroll == NO) {
            BOOL isInsertedToTableView = [_delegate CEStreamADDidLoadAdAtIndexPath:targetIndexPath];

            if (isInsertedToTableView == NO) {
                [_adHolders removeObjectForKey:@(targetPosIndex)];
                [self.placementAdViewRecycled setObject:adView forKey:placement];
                viewDidInserted = NO;
                NSLog(@"inserted to table view:NO");
            }
        }

        if (viewDidInserted == YES) {
            [self updateAdStatus];
            [self decorateADView:(UIView *)adView];
            [self updateProhibitPosWithAdPos:targetPosIndex];
            ++_place;
            [self.placementLastAddedPosition setObject:[NSNumber numberWithInt:targetPosIndex] forKey:placement];
        }
    }
} /* onADLoaded */

#pragma mark - AD view
- (void) decorateADView:(UIView *)adView {
    adView.layer.shadowColor = [[UIColor blackColor] CGColor];
    adView.layer.shadowOffset = CGSizeMake(0.0f, 0.0f); // [horizontal offset, vertical offset]
    adView.layer.shadowOpacity = 1.0f; // 0.0 ~ 1.0
    adView.layer.shadowRadius = 1.0f;
}

- (void) updateAdStatus {
    
    NSMutableArray  *startHolders = [[NSMutableArray alloc] init];
    for (NSNumber * adPos in _adHolders) {
        CEADHolder * holder = [_adHolders objectForKey:adPos];
        BOOL isVisible = ([adPos intValue] >= _firstVisiblePosition && [adPos intValue] <= _lastVisiblePosition);

        if (!_isActive) {
            if (holder.isShowing == YES) {
                holder.isShowing = NO;
                [holder.adView onHide];
            }

            if (holder.isPlaying == YES) {
                holder.isPlaying = NO;
                [holder.adView onStop];
            }
        } else {
            if (holder.isPlaying == YES && isVisible == NO) {
                if (holder.isShowing == YES) {
                    holder.isShowing = NO;
                    [holder.adView onHide];
                }

                if ([_delegate isIdle]) {
                    holder.isPlaying = NO;
                    [holder.adView onStop];
                }
            } else if (holder.isPlaying == NO && isVisible == NO) {
                if (holder.isShowing == YES) {
                    holder.isShowing = NO;
                    [holder.adView onHide];
                }
            } else if (holder.isPlaying == NO && isVisible == YES) {
                if (holder.isShowing == NO) {
                    holder.isShowing = YES;
                    [holder.adView onShow];
                }

                if ([_delegate isIdle] && _enableAutoPlay) {
                    [startHolders addObject:adPos];
                }
            } else if (holder.isPlaying == YES && isVisible == YES) {
                if (holder.isShowing == NO) {
                    holder.isShowing = YES;
                    [holder.adView onShow];
                }
            }
        }
    }

    // for CEAVAudioSession, it must be order(start then stop).
    for (NSNumber *adPos in startHolders) {
         CEADHolder *holder = [_adHolders objectForKey:adPos];
         holder.isPlaying = YES;
         [holder.adView onStart];
    }
} /* updateAdStatus */

@end
