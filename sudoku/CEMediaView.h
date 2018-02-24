/*!
 * @header CEMediaView.h
 *
 * @brief Media view interface
 *
 * @author Intowow
 * @copyright 2016 intowow. All rights reserved.
 */

#import <UIKit/UIKit.h>
#import "CENativeAd.h"
#import "CEVideoViewProfile.h"

/*!
 *  MediaViewDelegate
 */
@protocol CEMediaViewDelegate;

/*!
 *  @brief CEMediaView class, native AD main media view
 */
@interface CEMediaView : UIControl

/*!
 *  @brief the delegate that receive MediaView event
 */
@property (nonatomic, weak, nullable) id<CEMediaViewDelegate> delegate;

/*!
 *  @brief the native AD instance that provide the AD component
 */
@property (nonatomic, strong, nullable) CENativeAd * nativeAd;

/*!
 *  @brief initializer function
 *
 *  @param nativeAd CENativeAd instance that can provide ad component
 *
 *  @return instance of CEMediaView
 */
- (nonnull instancetype) initWithNativeAd:(nonnull CENativeAd *)nativeAd;

/*!
 *  @brief initializer function
 *
 *  @param videoViewProfile profile for customized view.  Please check CEVideoViewProfileNativeMask for valid flags.
 *
 *  @return instance of CEMediaView
 */
- (nonnull instancetype) initWithVideoViewProfile:(CEVideoViewProfile)videoViewProfile;


/*!
 *  @brief destroy the cache ad in media view
 */
- (void) destroy;

/*!
 *  @brief start the video ad play
 */
- (void) play;

/*!
 *  @brief stop the video ad play
 */
- (void) stop;

/*!
 *  @brief mute the video
 */
- (void) mute;

/*!
 *  @brief unmute the video
 */
- (void) unmute;

/*!
 *  @brief check the video volume state
 */
- (BOOL)isMute;

@end

/*!
 *  @brief protocol of CEMediaViewDelegate that can receive media view events
 */
@protocol CEMediaViewDelegate <NSObject>

@optional
/*!
 *  @brief callback while media view is loaded successfully
 *
 *  @param mediaView media view
 */
- (void) mediaViewDidLoad:(nonnull CEMediaView *)mediaView;

/*!
 *  @brief callback while fail to load a media view
 *
 *  @param mediaView media view
 *  @param error indicates the fail reason
 */
- (void) mediaView:(nonnull CEMediaView *)mediaView didFailWithError:(nonnull NSError *)error;

@end

