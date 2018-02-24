/*!
 * @header CEInStreamAD.h
 *
 * @brief CE In-Stream ad interface
 *
 * @author Intowow
 * @copyright 2017 intowow. All rights reserved.
 */

#import <Foundation/Foundation.h>
#import "I2WAPI.h"
#import "CEVideoViewProfile.h"

#define kCECurrentADNumInvalid -1
#define kCEToTalADNumInvalid -1
#define kCEADBreakRemainTimeInvalid -1
#define kCEADRemainTimeInvalid -1

@protocol CEInStreamADDelegate, CEContentProgressProvider;


/*!
 *  @brief CEInStreamAD provide an easy way to integrate In-Stream format AD
 */
@interface CEInStreamAD : NSObject

/*!
 *  @brief the delegate that receive CEInStreamAD events
 */
@property (nonatomic, weak, nullable) id<CEInStreamADDelegate> delegate;

/*!
 *  @brief the content progress provider
 */
@property (nonatomic, weak, nullable) id<CEContentProgressProvider> progressProvider;

/*!
 *  @brief the Ad property can get more information.
 */
@property (nonatomic, strong, readonly, nullable) Ad * ad;

/*!
 *  @brief the unique token identifier for current in-stream AD
 */
@property (nonatomic, strong, readonly, nullable) NSString * adToken;

/*!
 *  @brief init CEInStreamAD with AD placement name
 *
 *  @param placement AD placement name
 *  @param adContainer view for ad container
 *  @param videoViewProfile profile for customized view. Please check CEVideoViewProfileInStreamMask for valid flags.
 *
 *  @return CEInStreamAD instance
 */
- (nonnull instancetype) initWithPlacement:(nonnull NSString *)placement
                               adContainer:(nonnull UIView*)adContainer
                          videoViewProfile:(CEVideoViewProfile)videoViewProfile;

/*!
 *  @brief register view for AD dismiss
 *
 *  @param view the view for dismiss ad
 */
- (void) registerViewForDismiss:(nonnull UIView *)view;

/*!
 *  @brief for viewability tracking, register views when it will cover ad
 *
 *  @param views the views will cover ad
 */
- (void) registerFriendlyObstruction:(nonnull NSArray<UIView *>*)views;

/*!
*  @brief automatically request in-stream ads based on cue points
*/
- (void) startAutoRequestAD;

/*!
 *  @brief content video reach end
 */
- (void) contentComplete;

/*!
 *  @brief call play to trigger ad video play
 */
- (void) play;

/*!
 *  @brief call stop to stop ad video/animation play
 */
- (void) stop;

/*!
 *  @brief call destroy to destroy in-stream ad
 */
- (void) destroy;

/*!
 *  @brief get array of cue points in milli-second
 *  will return nil when we can not get total duration of content video
 */
- (nullable NSArray<NSNumber *>*) getCuePoints;

/*!
 *  @brief get current ad number for the playing ad break
 *  If there's no ad break playing, this will return 'kCECurrentADNumInvalid'
 */
- (int) getCurrentADNum;

/*!
 *  @brief get total ad number for the playing ad break
 *  Following situation will return 'kCEToTalADNumInvalid'
 *  1. If there's no ad break playing.
 *  2. ADBreak type is 'Fixed time'.
 */
- (int) getTotalADNum;

/*!
 *  @brief get the remain time for current playing ad break
 *  Following situation will return 'kCEADBreakRemainTimeInvalid'
 *  1. If there's no ad break playing
 *  2. ADBreak type is 'Multi ADs'.
 */
- (CEMilliSec) getADBreakRemainTime;

/*!
 *  @brief get the remain time for playing ad
 *  If there's no ad break playing, this will return 'kCEADRemainTimeInvalid'
 */
- (CEMilliSec) getADRemainTime;

@end

#pragma mark - CEInStreamADDelegate
/*!
 *  @brief protocol CEInStreamADDelegate that can receive AD events
 */
@protocol CEInStreamADDelegate <NSObject>
@optional

/*!
 *  @brief callback while fail to load an in-stream ad from CrystalExpressSDK
 *
 *  @param inStreamAD CEInStreamAD instance that own this in-stream ad component
 *  @param error error indicates the fail reason
 */
- (void) inStreamADDidFail:(nonnull CEInStreamAD *)inStreamAD withError:(nullable NSError *)error;

/*!
 *  @brief callback while this in-stream video ad playback is started.
 *
 *  @param inStreamAD CEInStreamAD instance that own this in-stream ad component
 */
- (void) inStreamADDidVideoStart:(nonnull CEInStreamAD *)inStreamAD;

/*!
 *  @brief callback while this in-stream video ad playback is ended.
 *
 *  @param inStreamAD CEInStreamAD instance that own this in-stream ad component
 */
- (void) inStreamADDidVideoEnd:(nonnull CEInStreamAD *)inStreamAD;

/*!
 *  @brief callback while this in-stream ad is clicked by user
 *
 *  @param inStreamAD CEInStreamAD instance that own this in-stream ad component
 */
- (void) instreamADDidClick:(nonnull CEInStreamAD *)inStreamAD;

/*!
 *  @brief callback while this in-stream video ad is muted.
 *
 *  @param inStreamAD CEInStreamAD instance that own this in-stream ad component
 */
- (void) instreamADDidMute:(nonnull CEInStreamAD *)inStreamAD;

/*!
 *  @brief callback while this in-steam video ad is unmuted.
 *
 *  @param inStreamAD CEInStreamAD instance that own this in-stream ad component
 */
- (void) instreamADDidUnmute:(nonnull CEInStreamAD *)inStreamAD;

/*!
 *  @brief callback while in-stream ad is about to log impression
 *
 *  @param inStreamAD CEInStreamAD instance that own this in-stream ad component
 */
- (void) inStreamADWillTrackImpression:(nonnull CEInStreamAD *)inStreamAD;

/*!
 *  @brief callback while this in-stream ad cue points prepare ready
 *
 *  @param inStreamAD CEInStreamAD instance that own this in-stream ad component
 */
- (void) inStreamADCuePointReady:(nonnull CEInStreamAD *)inStreamAD;

/*!
 *  @brief callback the progress state of this in-stream video.
 *
 *  @param inStreamAD CEInStreamAD instance that own this in-stream ad component
 *  @param currentPosition this video current play back position time (ms)
 */
- (void) inStreamProgress:(nonnull CEInStreamAD *)inStreamAD
                 duration:(CEMilliSec)totalDuration
                 position:(CEMilliSec)currentPosition;

/*!
 *  @brief callback while this in-stream ad request content to pause because ad is about to start
 *
 *  @param inStreamAD CEInStreamAD instance that own this in-stream ad component
 *  @param adBreakType CEADBreakTYpe indicates the type of the presenting ad break
 *  @param cuePoint CEMilliSec indicates the cue point that ad presenting
 */
- (void) inStreamADRequestContentPause:(nonnull CEInStreamAD *)inStreamAD
                           adBreakType:(CEADBreakType)adBreakType
                              cuePoint:(CEMilliSec)cuePoint;

/*!
 *  @brief callback while this in-stream ad request content to resume because ad is ended or skipped
 *
 *  @param inStreamAD CEInStreamAD instance that own this in-stream ad component
 *  @param adRemainTime CEMilliSec remaining time for this ad if ad is not reach end
 */
- (void) inStreamADRequestContentResume:(nonnull CEInStreamAD *)inStreamAD
                           adRemainTime:(CEMilliSec)adRemainTime;

@end

@protocol CEContentProgressProvider <NSObject>
/*!
 *  @brief provide content progress
 */
- (NSTimeInterval) getContentCurrentPosition;

/*!
 *  @brief provide content total duration
 */
- (NSTimeInterval) getContentTotalDuration;

/*!
 *  @brief tell SDK whether content player is ready
 */
- (BOOL) isContentPlayerReady;
@end
