/*!
 * @header CENativeAd.h
 *
 * @brief CE native ad interface
 *
 * @author Intowow
 * @copyright 2016 intowow. All rights reserved.
 */

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "I2WAPI.h"

@class CEAdImage;
@protocol CENativeAdDelegate;

/*!
 *  @brief CENativeAd provide an easy way to integrate native format AD
 */
@interface CENativeAd : NSObject

/*!
 *  @brief AD placement string
 */
@property (nonatomic, copy, readonly, nonnull) NSString * placement;

/*!
 *  @brief AD title
 */
@property (nonatomic, copy, readonly, nullable) NSString * title;

/*!
 *  @brief AD subtitle
 */
@property (nonatomic, copy, readonly, nullable) NSString * subTitle;

/*!
 *  @brief AD call to action string
 */
@property (nonatomic, copy, readonly, nullable) NSString * callToAction;

/*!
 *  @brief AD icon image
 */
@property (nonatomic, strong, readonly, nullable) CEAdImage * icon;

/*!
 *  @brief AD descripstion body string
 */
@property (nonatomic, copy, readonly, nullable) NSString * body;

/*!
 *  @brief the unique token identifier for current native AD
 */
@property (nonatomic, strong, nullable) NSString * adToken;

/*!
 *  @brief the delegate that receive CENativeAd events
 */
@property (nonatomic, weak, nullable) id<CENativeAdDelegate> delegate;

/*!
 *  @brief decide whether volume control is auto
 */
@property (nonatomic, assign) BOOL isAutoVolumeControl DEPRECATED_ATTRIBUTE;

/*!
 *  @brief the Ad property can get more information.
 */
@property (nonatomic, strong, readonly, nullable) Ad * ad;

/*!
 *  @brief the path of video cover image.
 */
@property (nonatomic, strong, readonly, nullable) NSString * coverImagePath;

/*!
 *  @brief initializer of CENativeAd
 *
 *  @param placement AD placement string
 *
 *  @return CENativeAd instance
 */
- (nonnull instancetype) initWithPlacement:(nonnull NSString *)placement NS_DESIGNATED_INITIALIZER;

/*!
 *  @brief register view for AD interaction
 *
 *  @param view           the container view for native ad
 *  @param viewController the viewcontroller that has the native ad container view
 */
- (void) registerViewForInteraction:(nonnull UIView *)view
    withViewController:(nonnull UIViewController *)viewController;

/*!
 *  @brief register clickable views for AD interaction instead of container view
 *
 *  @param view           the container view for native ad
 *  @param viewController the viewcontroller that has the native ad container view
 *  @param clickableViews the clickable views that allowed user interaction
 */
- (void) registerViewForInteraction:(nonnull UIView *)view
    withViewController:(nonnull UIViewController *)viewController
    withClickableViews:(nonnull NSArray *)clickableViews;

/*!
 *  @brief unregister previous native ad view
 */
- (void) unregisterView;

/*!
 *  @brief request native ad from CrystalExpressSDK
 */
- (void) loadAd;

/*!
 *  @brief request native ad from CrystalExpressSDK
 *
 *  @param timeout second to wait for native ad
 */
- (void) loadAdWithTimeout:(int)timeout;

/*!
 *  @brief check whether has video assset.
 */
- (BOOL) hasVideoContent;

/*!
 *  @brief total size of files downloaded.
 */
- (long long)getTotalFileSize;
@end

#pragma mark - CEAdImage
/*!
 *  @brief CEAdImage class
 */
@interface CEAdImage : NSObject

/*!
 *  @brief the url for ad image data
 */
@property (nonatomic, copy, readonly, nonnull) NSURL * url;

/*!
 *  @brief the width of image
 */
@property (nonatomic, assign, readonly) NSInteger width;

/*!
 *  @brief the height of image
 */
@property (nonatomic, assign, readonly) NSInteger height;

/*!
 *  @brief initialize CEAdImage from local file path
 *
 *  @param filePath string of local path
 *
 *  @return CEAdImage instance
 */
- (nonnull instancetype) initWithFilePath:(nonnull NSString *)filePath;

/*!
 *  @brief initialize CEAdImage from NSURL
 *
 *  @param url    url of image data
 *  @param width  image width
 *  @param height image height
 *
 *  @return CEAdImage instance
 */
- (nonnull instancetype) initWithURL:(nonnull NSURL *)url width:(NSInteger)width height:(NSInteger)height NS_DESIGNATED_INITIALIZER;

/*!
 *  @brief load image data asynchronously
 *
 *  @param block the callback block while image is loaded
 */
- (void) loadImageAsyncWithBlock:(nullable void (^)(UIImage * __nullable image))block;

@end

#pragma mark - CENativeAdDelegate
/*!
 *  @brief protocol of CENativeAdDelegate that can receive AD events
 */
@protocol CENativeAdDelegate <NSObject>

@optional
/*!
 *  @brief callback while native ad component is loaded from CrystalExpressSDK
 *
 *  @param nativeAd CENativeAd instance that own this native ad component
 */
- (void) nativeAdDidLoad:(nonnull CENativeAd *)nativeAd;

/*!
 *  @brief callback while native ad is about to log impression
 *
 *  @param nativeAd CENativeAd instance
 */
- (void) nativeAdWillTrackImpression:(nonnull CENativeAd *)nativeAd;

/*!
 *  @brief callback while fail to load a native ad from CrystalExpressSDK
 *
 *  @param nativeAd CENativeAd instance that own this native ad component
 *  @param error    error indicates the fail reason
 */
- (void) nativeAd:(nonnull CENativeAd *)nativeAd didFailWithError:(nonnull NSError *)error;

/*!
 *  @brief callback while this native ad is clicked by user
 *
 *  @param nativeAd CENativeAd instance that own this native ad component
 */
- (void) nativeAdDidClick:(nonnull CENativeAd *)nativeAd;

/*!
 *  @brief callback while native ad finished handle click event
 *
 *  @param nativeAd CENativeAd instance that own this native ad component
 */
- (void) nativeAdDidFinishHandlingClick:(nonnull CENativeAd *)nativeAd;

/*!
 *  @brief callback while this native ad is video format and muted.
 *
 *  @param nativeAd CENativeAd instance that own this native ad component
 */
- (void) nativeAdDidMute:(nonnull CENativeAd *)nativeAd;

/*!
 *  @brief callback while this native ad is video format and unmuted.
 *
 *  @param nativeAd CENativeAd instance that own this native ad component
 */
- (void) nativeAdDidUnmute:(nonnull CENativeAd *)nativeAd;

/*!
 *  @brief callback while this native ad is video format and start playback.
 *
 *  @param nativeAd CENativeAd instance that own this native ad component
 */
- (void) nativeAdDidVideoStart:(nonnull CENativeAd *)nativeAd;

/*!
 *  @brief callback while this native ad is video format and playback to end.
 *
 *  @param nativeAd CENativeAd instance that own this native ad component
 */
- (void) nativeAdDidVideoEnd:(nonnull CENativeAd *)nativeAd;

/*!
 *  @brief callback while this native ad is video format and progress state.
 *
 *  @param nativeAd CENativeAd instance that own this native ad component
 *  @param totalDuration this video total duration time (ms)
 *  @param currentPosition this video current play back position time (ms)
 */
- (void) nativeAdDidVideoProgress:(nonnull CENativeAd *)nativeAd
    duration:(int)totalDuration
    position:(int)currentPosition;

/*!
 *  @brief callback while this native ad is failed to render.
 *
 *  @param nativeAd CENativeAd instance that own this native ad component
 *  @param error NSError error for rendering
 */
- (void) nativeAdOnFailedToRender:(nonnull CENativeAd *)nativeAd error:(nonnull NSError *)error;
@end
