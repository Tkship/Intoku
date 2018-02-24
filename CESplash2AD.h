/*!
 * @header CESplash2AD.h
 *
 * @brief CE splash2 ad interface
 *
 * @author Intowow
 * @copyright 2016 intowow. All rights reserved.
 */

#import <Foundation/Foundation.h>
#import "I2WAPI.h"

@protocol CESplash2ADDelegate;

/*!
 *  @brief Portrait present animation option
 */
typedef NS_ENUM (NSUInteger, CEPortraitPresentAnimationOption) {
    /*!
     *  iOS default animation
     */
    CE_SPLASH2_PORTRAIT_PRESENT_DEFAULT,
    /*!
     *  vertical bounce present animation
     */
    CE_SPLASH2_PORTRAIT_PRESENT_VERTICAL_BOUNCE,
};

/*!
 *  @brief Portrait dismiss animation option
 */
typedef NS_ENUM (NSUInteger, CEPortraitDismissAnimationOption) {
    /*!
     *  iOS default animation
     */
    CE_SPLASH2_PORTRAIT_DISMISS_DEFAULT,
};

/*!
 *  @brief Landscape present animation option
 */
typedef NS_ENUM (NSUInteger, CELandscapePresentAnimationOption) {
    /*!
     *  iOS default animation
     */
    CE_SPLASH2_LANDSCAPE_PRESENT_DEFAULT,
    /*!
     *  rotation from portrait to landscape animation
     */
    CE_SPLASH2_LANDSCAPE_PRESENT_ROTATION,
};

/*!
 *  @brief Landscape dismiss animation option
 */
typedef NS_ENUM (NSUInteger, CELandscapeDismissAnimationOption) {
    /*!
     *  iOS default animation
     */
    CE_SPLASH2_LANDSCAPE_DISMISS_DEFAULT,
    /*!
     *  rotation from landscape to portrait animation
     */
    CE_SPLASH2_LANDSCAPE_DISMISS_ROTATION,
};

/*!
 *  @brief CESplash2AD provide API to request Splash AD format
 */
@interface CESplash2AD : NSObject

/*!
 *  @brief the delegate that receive CESplash2AD events
 */
@property (nonatomic, weak, nullable) id<CESplash2ADDelegate> delegate;

/*!
 *  @brief the Ad property can get more information.
 */
@property (nonatomic, strong, readonly, nullable) Ad * ad;

/*!
 *  @brief init CESplash2AD with AD placement name
 *
 *  @param placement AD placement name
 *
 *  @return CESplash2AD instance
 */
- (nonnull instancetype) initWithPlacement:(nonnull NSString *)placement NS_DESIGNATED_INITIALIZER;

/*!
 *  @brief Starts loading ad content process.
 */
- (void) loadAd;

/*!
 *  @brief Starts loading ad content process.
 *
 *  @param timeout second to wait for splash2 ad
 */
- (void) loadAdWithTimeout:(int)timeout;

/*!
 *  @brief return whether viewcontroller is a Splash Ad viewcontroller
 *
 *  @param vc viewcontroller
 *
 *  @return bool to indicate viewcontroller is a CrystalExpress Splash AD viewcontroller
 */
- (BOOL) isSplashAdVC:(nonnull UIViewController *)vc;

/*!
 *  @brief Presents the splash ad modally from viewCotroller
 *
 *  @param viewController view controller from which splash ad will be presented.
 *  @param animated       animate presenting
 */
- (void) showFromViewController:(nonnull UIViewController *)viewController
    animated:(BOOL)animated;

/*!
 *  @brief dismiss splash view controller
 *
 *  @param animated animate presenting
 */
- (void) dismissAnimated:(BOOL)animated;

/*!
 *  @brief dismiss splash view controller automatically after user had engage this Ad
 *
 *  @param dismissAd boolValue indicate whether to dismiss ad
 */
- (void) setDismissAdAfterEngageAd:(BOOL)dismissAd;

/*!
 *  @brief set portrait splash AD present and dismiss animation with CrystalExpress bulit-in animation effect
 *
 *  @param presentAnimation viewcontroller present animation
 *  @param dismissAnimation viewcontroller dismiss animation
 */
- (void) setPortraitViewControllerPresentAnimation:(CEPortraitPresentAnimationOption)presentAnimation
    dismissAnimation:(CEPortraitDismissAnimationOption)dismissAnimation;

/*!
 *  @brief set landscape splash AD present and dismiss animation with CrystalExpress bulit-in animation effect
 *
 *  @param presentAnimation viewcontroller present animation
 *  @param dismissAnimation viewcontroller dismiss animation
 */
- (void) setLandscapeViewControllerPresentAnimation:(CELandscapePresentAnimationOption)presentAnimation
    dismissAnimation:(CELandscapeDismissAnimationOption)dismissAnimation;

/*!
 *  @brief Splash AD allowed customized present/dismiss animation
 *
 *  @param presentAnimation animation object which conform to UIViewControllerAnimatedTransitioning
 *  @param dismissAnimation animation object which conform to UIViewControllerAnimatedTransitioning
 */
- (void) setCustomPortraitViewControllerPresentAnimation:(nonnull id<UIViewControllerAnimatedTransitioning>)presentAnimation
    dismissAnimation:(nonnull id<UIViewControllerAnimatedTransitioning>)dismissAnimation;
- (void) setCustomLandscapeViewControllerPresentAnimation:(nonnull id<UIViewControllerAnimatedTransitioning>)presentAnimation
    dismissAnimation:(nonnull id<UIViewControllerAnimatedTransitioning>)dismissAnimation;

/*!
 *  @brief total size of files downloaded.
 */
- (long long)getTotalFileSize;
@end

#pragma mark - CESplash2ADDelegate
/*!
 *  @brief protocol of CESplash2ADDelegate that can receive AD events
 */
@protocol CESplash2ADDelegate <NSObject>
@optional
/*!
 *  @brief callback while splash2 ad component is loaded from CrystalExpressSDK
 *
 *  @param splash2AD CESplash2AD instance that own this splash2 ad component
 */
- (void) splash2ADDidLoaded:(nonnull CESplash2AD *)splash2AD;

/*!
 *  @brief callback while fail to load a splash ad from CrystalExpressSDK
 *
 *  @param splash2AD CESplash2AD instance that own this splash2 ad component
 *  @param error  error indicates the fail reason
 */
- (void) splash2ADDidFail:(nonnull CESplash2AD *)splash2AD withError:(nullable NSError *)error;

/*!
 *  @brief callback while this splash2 ad is clicked by user
 *
 *  @param splash2AD CESplash2AD instance that own this splash2 ad component
 */
- (void) splash2ADDidClick:(nonnull CESplash2AD *)splash2AD;

/*!
 *  @brief callback while splash2 ad is about to log impression
 *
 *  @param splash2AD CESplash2AD instance that own this splash2 ad component
 */
- (void) splash2ADWillTrackImpression:(nonnull CESplash2AD *)splash2AD;

/*!
 *  @brief callback while this splash2 ad is video format and muted.
 *
 *  @param splash2AD CESplash2AD instance that own this splash2 ad component
 */
- (void) splash2ADDidMute:(nonnull CESplash2AD *)splash2AD;

/*!
 *  @brief callback while this splash2 ad is video format and unmuted.
 *
 *  @param splash2AD CESplash2AD instance that own this splash2 ad component
 */
- (void) splash2ADDidUnmute:(nonnull CESplash2AD *)splash2AD;

/*!
 *  @brief callback while this splash2 ad is video format and start playback.
 *
 *  @param splash2AD CESplash2AD instance that own this splash2 ad component
 */
- (void) splash2ADDidVideoStart:(nonnull CESplash2AD *)splash2AD;

/*!
 *  @brief callback while this splash2 ad is video format and playback to end.
 *
 *  @param splash2AD CESplash2AD instance that own this splash2 ad component
 */
- (void) splash2ADDidVideoEnd:(nonnull CESplash2AD *)splash2AD;

/*!
 *  @brief callback while this splash2 ad is video format and progress state.
 *
 *  @param splash2AD CESplash2AD instance that own this splash2 ad component
 *  @param totalDuration this video total duration time (ms)
 *  @param currentPosition this video current play back position time (ms)
 */
- (void) splash2ADDidVideoProgress:(nonnull CESplash2AD *)splash2AD
    duration:(int)totalDuration
    position:(int)currentPosition;

/*!
 *  @brief callback function while splash2 AD did display from screen
 *
 *  @param splash2AD CESplash2AD instance that own this splash2 ad component
 */
- (void) splash2ADDidDisplayed:(nonnull CESplash2AD *)splash2AD;

/*!
 *  @brief callback function while splash2 AD did dismiss from screen
 *
 *  @param splash2AD CESplash2AD instance that own this splash2 ad component
 */
- (void) splash2ADDidDismiss:(nonnull CESplash2AD *)splash2AD;

/*!
 *  @brief callback function while splash2 AD will display to screen
 *
 *  @param splash2AD CESplash2AD instance that own this splash2 ad component
 */
- (void) splash2ADWillDisplay:(nonnull CESplash2AD *)splash2AD;

/*!
 *  @brief callback function while splash2 AD will dismiss from screen
 *
 *  @param splash2AD CESplash2AD instance that own this splash2 ad component
 */
- (void) splash2ADWillDismiss:(nonnull CESplash2AD *)splash2AD;
@end
