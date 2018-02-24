//
//  CEStreamTagADHelper.h
//  crystalexpress
//
//  Copyright © 2015 intowow. All rights reserved.
//

#import "CEStreamADHelper.h"

@interface CEStreamTagADHelper : CEStreamADHelper
- (instancetype) initWithAdTag:(NSString *)adTag delegate:(id<CEStreamAdHelperDelegate>)delegate;
- (void) checkShouldLoadAdWithPosition:(int)targetInsertPosIndex;
@end
