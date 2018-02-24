/*!
 * @header CERewardedVideoAD.h
 *
 * @brief CE Rewarded ad interface
 *
 * @author Intowow
 * @copyright 2017 intowow. All rights reserved.
 */

#import <Foundation/Foundation.h>
#import "I2WAPI.h"

@protocol CERewardedVideoADDelegate;


@interface CERewardedVideoAD : NSObject

/*!
 *  @brief the delegate that receive CERewardedVideoAD events
 */
@property (nonatomic, weak, nullable) id<CERewardedVideoADDelegate> delegate;

/*!
 *  @brief the Ad property can get more information.
 */
@property (nonatomic, strong, readonly, nullable) Ad * ad;

/*!
 *  @brief init CERewardedVideoAD with AD placement name
 *
 *  @param placement AD placement name
 *
 *  @return CERewardedVideoAD instance
 */
- (nonnull instancetype) initWithPlacement:(nonnull NSString *)placement NS_DESIGNATED_INITIALIZER;

/*!
 *  @brief Starts loading ad content process.
 */
- (void) loadAd;

/*!
 *  @brief Starts loading ad content process.
 *
 *  @param timeout second to wait for rewardedVideo ad
 */
- (void) loadAdWithTimeout:(int)timeout;

/*!
 *  @brief return whether viewcontroller is a rewardedVideo Ad viewcontroller
 *
 *  @param vc viewcontroller
 *
 *  @return bool to indicate viewcontroller is a CrystalExpress rewardedVideo AD viewcontroller
 */
- (BOOL) isRewardedVideoAdVC:(nonnull UIViewController *)vc;

/*!
 *  @brief Presents the rewardedVideo ad modally from viewCotroller
 *
 *  @param viewController view controller from which rewardedVideo ad will be presented.
 *  @param animated       animate presenting
 */
- (void) showFromViewController:(nonnull UIViewController *)viewController
                       animated:(BOOL)animated;

/*!
 *  @brief dismiss rewardedVideo view controller
 *
 *  @param animated animate presenting
 */
- (void) dismissAnimated:(BOOL)animated;

/*!
 *  @brief total size of files downloaded.
 */
- (long long)getTotalFileSize;

@end


#pragma mark - CERewardedVideoADDelegate
/*!
 *  @brief protocol of CERewardedVideoADDelegate that can receive AD events
 */
@protocol CERewardedVideoADDelegate <NSObject>
@optional
/*!
 *  @brief callback while rewardedVideo ad component is loaded from CrystalExpressSDK
 *
 *  @param rewardedVideoAD CERewardedVideoAD instance that own this rewardedVideo ad component
 */
- (void) rewardedVideoADDidLoaded:(nonnull CERewardedVideoAD *)rewardedVideoAD;

/*!
 *  @brief callback while fail to load a rewardedVideo ad from CrystalExpressSDK
 *
 *  @param rewardedVideoAD CERewardedVideoAD instance that own this rewardedVideo ad component
 *  @param error error indicates the fail reason
 */
- (void) rewardedVideoADDidFail:(nonnull CERewardedVideoAD *)rewardedVideoAD withError:(nullable NSError *)error;

/*!
 *  @brief callback while this rewardedVideo ad is clicked by user
 *
 *  @param rewardedVideoAD CERewardedVideoAD instance that own this rewardedVideo ad component
 */
- (void) rewardedVideoADDidClick:(nonnull CERewardedVideoAD *)rewardedVideoAD;

/*!
 *  @brief callback while this rewardedVideo ad is video format and muted.
 *
 *  @param rewardedVideoAD CERewardedVideoAD instance that own this rewardedVideo ad component
 */
- (void) rewardedVideoADDidMute:(nonnull CERewardedVideoAD *)rewardedVideoAD;

/*!
 *  @brief callback while this rewardedVideo ad is video format and unmuted.
 *
 *  @param rewardedVideoAD CERewardedVideoAD instance that own this rewardedVideo ad component
 */
- (void) rewardedVideoADDidUnmute:(nonnull CERewardedVideoAD *)rewardedVideoAD;

/*!
 *  @brief callback while rewardedVideo ad impression
 *
 *  @param rewardedVideoAD CERewardedVideoAD instance that own this rewardedVideo ad component
 */
- (void) rewardedVideoADImpression:(nonnull CERewardedVideoAD *)rewardedVideoAD;

/*!
 *  @brief callback while this rewardedVideo ad is video format and start playback.
 *
 *  @param rewardedVideoAD CERewardedVideoAD instance that own this rewardedVideo ad component
 */
- (void) rewardedVideoADDidVideoStart:(nonnull CERewardedVideoAD *)rewardedVideoAD;

/*!
 *  @brief callback while this rewardedVideo ad reward user.
 *
 *  @param rewardedVideoAD CERewardedVideoAD instance that own this rewardedVideo ad component
 */
- (void) rewardedVideoADDidRewardUser:(nonnull CERewardedVideoAD *)rewardedVideoAD;

/*!
 *  @brief callback while this rewardedVideo ad is video format and playback to end.
 *
 *  @param rewardedVideoAD CERewardedVideoAD instance that own this rewardedVideo ad component
 */
- (void) rewardedVideoADDidVideoEnd:(nonnull CERewardedVideoAD *)rewardedVideoAD;

/*!
 *  @brief callback while this rewardedVideo ad is video format and progress state.
 *
 *  @param rewardedVideoAD CERewardedVideoAD instance that own this rewardedVideo ad component
 *  @param totalDuration this video total duration time (ms)
 *  @param currentPosition this video current play back position time (ms)
 */
- (void) rewardedVideoADDidVideoProgress:(nonnull CERewardedVideoAD *)rewardedVideoAD
                                duration:(int)totalDuration
                                position:(int)currentPosition;

/*!
 *  @brief callback function while rewardedVideo AD did display from screen
 *
 *  @param rewardedVideoAD CERewardedVideoAD instance that own this rewardedVideo ad component
 */
- (void) rewardedVideoADDidDisplayed:(nonnull CERewardedVideoAD *)rewardedVideoAD;

/*!
 *  @brief callback function while rewardedVideo AD did dismiss from screen
 *
 *  @param rewardedVideoAD CERewardedVideoAD instance that own this rewardedVideo ad component
 */
- (void) rewardedVideoADDidDismiss:(nonnull CERewardedVideoAD *)rewardedVideoAD;

/*!
 *  @brief callback function while rewardedVideo AD will display to screen
 *
 *  @param rewardedVideoAD CERewardedVideoAD instance that own this rewardedVideo ad component
 */
- (void) rewardedVideoADWillDisplay:(nonnull CERewardedVideoAD *)rewardedVideoAD;

/*!
 *  @brief callback function while rewardedVideo AD will dismiss from screen
 *
 *  @param rewardedVideoAD CERewardedVideoAD instance that own this rewardedVideo ad component
 */
- (void) rewardedVideoADWillDismiss:(nonnull CERewardedVideoAD *)rewardedVideoAD;
@end
