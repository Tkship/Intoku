//
//  MoatPassiveVideoTracker.h
//  MoatMobileAppKit
//
//  Copyright © 2016 Moat. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "IWOWMoatAdEvent.h"
#import "IWOWMoatBaseTracker.h"

typedef enum IWOWMoatTrackerState : NSUInteger {
    MTStateUninitialized
    , MTStateInitialized
    , MTStateTracking
    , MTStateDestroyed
} IWOWMoatTrackerState;

@interface IWOWMoatReactiveVideoTracker : IWOWMoatBaseTracker

@property (readonly) IWOWMoatTrackerState state;

+ (IWOWMoatReactiveVideoTracker *)trackerWithPartnerCode:(NSString *)partnerCode;

- (bool)trackVideoAd:(NSDictionary *)adIds
            withLayer:(CALayer *)layer
   withContainingView:(UIView *)view
   withDurationMillis:(NSTimeInterval) duration;

- (void)dispatchEvent:(IWOWMoatAdEvent *)event;

- (void)changeTargetLayer:(CALayer *)newLayer
        withContainingView:(UIView *)view;

- (void)stopTracking;

@end
