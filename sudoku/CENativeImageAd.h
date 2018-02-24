/*!
 * @header CENativeImageAd.h
 *
 * @brief CE native image ad interface
 *
 * @author Intowow
 * @copyright 2017 intowow. All rights reserved.
 */

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "CENativeAd.h"

@protocol CENativeImageAdDelegate;

/*!
 *  @brief CENativeImageAd provide an easy way to integrate native image format AD
 */
@interface CENativeImageAd : NSObject

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
 *  @brief the delegate that receive CENativeImageAd events
 */
@property (nonatomic, weak, nullable) id<CENativeImageAdDelegate> delegate;

/*!
 *  @brief the Ad property can get more information.
 */
@property (nonatomic, strong, readonly, nullable) Ad * ad;

/*!
 *  @brief the path of image for display ad.
 */
@property (nonatomic, strong, readonly, nullable) NSString * adImagePath;

/*!
 *  @brief initializer of CENativeImageAd
 *
 *  @param placement AD placement string
 *
 *  @return CENativeImageAd instance
 */
- (nonnull instancetype) initWithPlacement:(nonnull NSString *)placement NS_DESIGNATED_INITIALIZER;

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
 *  @brief total size of files downloaded.
 */
- (long long)getTotalFileSize;

/*!
 *  @brief native image ad will handle impression
 */
- (void) handleImpression;

/*!
 *  @brief native image ad handle did render
 */
- (void) handleDidRenderWithContainerView:(nullable UIView *)container;

@end

#pragma mark - CENativeImageAdDelegate
/*!
 *  @brief protocol of CENativeAdDelegate that can receive AD events
 */
@protocol CENativeImageAdDelegate <NSObject>

@optional
/*!
 *  @brief callback while native image ad component is loaded from CrystalExpressSDK
 *
 *  @param nativeImageAd CENativeImageAd instance that own this native ad component
 */
- (void) nativeImageAdDidLoad:(nonnull CENativeImageAd *)nativeImageAd;

/*!
 *  @brief callback while native image ad is about to log impression
 *
 *  @param nativeImageAd CENativeImageAd instance
 */
- (void) nativeImageAdWillTrackImpression:(nonnull CENativeImageAd *)nativeImageAd;

/*!
 *  @brief callback while fail to load a native image ad from CrystalExpressSDK
 *
 *  @param nativeImageAd CENativeImageAd instance that own this native ad component
 *  @param error    error indicates the fail reason
 */
- (void) nativeImageAd:(nonnull CENativeImageAd *)nativeImageAd didFailWithError:(nonnull NSError *)error;

/*!
 *  @brief callback while this native image ad is clicked by user
 *
 *  @param nativeImageAd CENativeImageAd instance that own this native image ad component
 */
- (void) nativeImageAdDidClick:(nonnull CENativeImageAd *)nativeImageAd;

/*!
 *  @brief callback while native image ad finished handle click event
 *
 *  @param nativeImageAd CENativeImageAd instance that own this native image ad component
 */
- (void) nativeImageAdDidFinishHandlingClick:(nonnull CENativeImageAd *)nativeImageAd;

/*!
 *  @brief callback while this native image ad is failed to render.
 *
 *  @param nativeImageAd CENativeImageAd instance that own this native image ad component
 *  @param error NSError error for rendering
 */
- (void) nativeImageAdOnFailedToRender:(nonnull CENativeImageAd *)nativeImageAd error:(nonnull NSError *)error;
@end
