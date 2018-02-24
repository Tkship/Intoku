//
//  MoatAdEvent.h
//  MoatMobileAppKit
//
//  Created by Moat on 2/5/16.
//  Copyright © 2016 Moat. All rights reserved.
//
//  This class is simply a data object that encapsulates info relevant to a particular playback event.

#import <Foundation/Foundation.h>

typedef enum IWOWMoatAdEventType : NSUInteger {
    IWOWMoatAdEventComplete
    , IWOWMoatAdEventStart
    , IWOWMoatAdEventFirstQuartile
    , IWOWMoatAdEventMidPoint
    , IWOWMoatAdEventThirdQuartile
    , IWOWMoatAdEventSkipped
    , IWOWMoatAdEventStopped
    , IWOWMoatAdEventPaused
    , IWOWMoatAdEventPlaying
    , IWOWMoatAdEventVolumeChange
    , IWOWMoatAdEventNone
} IWOWMoatAdEventType;

static NSTimeInterval const IWOWMoatTimeUnavailable = NAN;
static float const IWOWMoatVolumeUnavailable = NAN;

@interface IWOWMoatAdEvent : NSObject

@property IWOWMoatAdEventType eventType;
@property NSTimeInterval adPlayhead;
@property float adVolume;
@property (readonly) NSTimeInterval timeStamp;

- (id)initWithType:(IWOWMoatAdEventType)eventType withPlayheadMillis:(NSTimeInterval)playhead;
- (id)initWithType:(IWOWMoatAdEventType)eventType withPlayheadMillis:(NSTimeInterval)playhead withVolume:(float)volume;
- (NSDictionary *)asDict;
- (NSString *)eventAsString;

@end
