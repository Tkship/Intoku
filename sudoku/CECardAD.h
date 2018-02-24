/*!
 * @header CECardAD.h
 *
 * @brief CE card ad interface
 *
 * @author Intowow
 * @copyright 2016 intowow. All rights reserved.
 */

#import <Foundation/Foundation.h>
#import "I2WAPI.h"
#import "CEVideoViewProfile.h"

@protocol CECardADDelegate;
/*!
 *  @brief CECardAD provide an easy way to integrate Card format AD
 */
@interface CECardAD : NSObject

/*!
 *  @brief the delegate that receive CECardAD events
 */
@property (nonatomic, weak, nullable) id<CECardADDelegate> delegate;

/*!
 *  @brief the Ad property can get more information.
 */
@property (nonatomic, strong, readonly, nullable) Ad * ad;

/*!
 *  @brief the unique token identifier for current card AD
 */
@property (nonatomic, strong, readonly, nullable) NSString * adToken;

/*!
 *  @brief the display ad view
 */
@property (nonatomic, strong, readonly, nullable) UIView * adUIView;

/*!
 *  @brief the path of video cover image.
 */
@property (nonatomic, strong, readonly, nullable) NSString * coverImagePath;

/*!
 *  @brief the aspect ratio of ad content. (Width / Height)
 *  It would be zero if the ad hasn't loaded.
 */
@property (nonatomic, assign, readonly) CGFloat aspectRatio;

/*!
 *  @brief init CECardAD with AD placement name
 *
 *  @param placement AD placement name
 *
 *  @return CECardAD instance
 */
- (nonnull instancetype) initWithPlacement:(nonnull NSString *)placement;

/*!
 *  @brief init CECardAD with AD placement name and CEVideoViewProfile
 *
 *  @param placement AD placement name
 *  @param videoViewProfile profile for customized view. Please check CEVideoViewProfileCardMask for valid flags.
 *
 *  @return CECardAD instance
 */
- (nonnull instancetype) initWithPlacement:(nonnull NSString *)placement
                          videoViewProfile:(CEVideoViewProfile)videoViewProfile NS_DESIGNATED_INITIALIZER;

/*!
 *  @brief starts loading ad content process.
 */
- (void) loadAd;

/*!
 *  @brief Starts loading ad content process.
 *
 *  @param timeout second to wait for card ad
 */
- (void) loadAdWithTimeout:(int)timeout;

/*!
 *  @brief starts loading ad content process with ad width.
 *
 *  @param adWidth AD width
 *  @param timeout second to wait for card ad
 */
- (void) loadAdWithAdWidth:(CGFloat)adWidth timeout:(int)timeout;

/*!
 *  @brief call show while ad is seen by user
 */
- (void) show;

/*!
 *  @brief call hide while ad is hide from user
 */
- (void) hide;

/*!
 *  @brief call play to trigger ad impression and video/animation play
 */
- (void) play;

/*!
 *  @brief call stop to stop ad video/animation play
 */
- (void) stop;

/*!
 *  @brief call mute to mute the video
 */
- (void) mute;

/*!
 *  @brief call unmute to unmute the video
 */
- (void) unmute;

/*!
 *  @brief check the video volume state
 */
- (BOOL) isMute;

/*!
 *  @brief check ad is the video content
 */
-(BOOL)hasVideoContent;

/*!
 *  @brief total size of files downloaded.
 */
- (long long)getTotalFileSize;
@end

#pragma mark - CECardADDelegate
/*!
 *  @brief protocol CECardADDelegate that can receive AD events
 */
@protocol CECardADDelegate <NSObject>
@optional
/*!
 *  @brief callback while card ad component is loaded from CrystalExpressSDK
 *
 *  @param cardAD CECardAD instance that own this card ad component
 */
- (void) cardADDidLoaded:(nonnull CECardAD *)cardAD;

/*!
 *  @brief callback while fail to load a card ad from CrystalExpressSDK
 *
 *  @param cardAD CECardAD instance that own this card ad component
 *  @param error error indicates the fail reason
 */
- (void) cardADDidFail:(nonnull CECardAD *)cardAD withError:(nullable NSError *)error;

/*!
 *  @brief callback while this card ad is clicked by user
 *
 *  @param cardAD CECardAD instance that own this card ad component
 */
- (void) cardADDidClick:(nonnull CECardAD *)cardAD;

/*!
 *  @brief callback while card ad is about to log impression
 *
 *  @param cardAD CECardAD instance that own this card ad component
 */
- (void) cardADWillTrackImpression:(nonnull CECardAD *)cardAD;

/*!
 *  @brief callback while this card ad is video format and muted.
 *
 *  @param cardAD CECardAD instance that own this card ad component
 */
- (void) cardADDidMute:(nonnull CECardAD *)cardAD;

/*!
 *  @brief callback while this card ad is video format and unmuted.
 *
 *  @param cardAD CECardAD instance that own this card ad component
 */
- (void) cardADDidUnmute:(nonnull CECardAD *)cardAD;

/*!
 *  @brief callback while this card ad is video format and start playback.
 *
 *  @param cardAD CECardAD instance that own this card ad component
 */
- (void) cardADDidVideoStart:(nonnull CECardAD *)cardAD;

/*!
 *  @brief callback while this card ad is video format and playback to end.
 *
 *  @param cardAD CECardAD instance that own this card ad component
 */
- (void) cardADDidVideoEnd:(nonnull CECardAD *)cardAD;

/*!
 *  @brief callback while this card ad is video format and progress state.
 *
 *  @param cardAD CECardAD instance that own this card ad component
 *  @param totalDuration this video total duration time (ms)
 *  @param currentPosition this video current play back position time (ms)
 */
- (void) cardADDidVideoProgress:(nonnull CECardAD *)cardAD
    duration:(int)totalDuration
    position:(int)currentPosition;

/*!
 *  @brief callback while this card ad ad view ready to do animation
 *
 *  @param cardAD CECardAD instance that own this card ad component
 *  @param adView current display ad view
 */
- (void) cardADOnPullDownAnimation:(nonnull CECardAD *)cardAD withAdView:(nullable UIView *)adView;

/**
 *  @brief callback while this card ad is failed to render
 *
 *  @param cardAD CECardAD instance that own this card ad component
 *  @param error Error for rendering
 */
- (void) cardADOnFailedToRender:(nonnull CECardAD *)cardAD error:(nonnull NSError *)error;
@end
