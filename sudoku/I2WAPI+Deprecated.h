//
//  I2WAPI+Deprecated.h
//  crystalsdk
//
//  Copyright © 2016 intowow. All rights reserved.
//

#import "I2WAPI.h"


@interface I2WAPI (Deprecated)

#pragma mark - testing API
/*!
 *  @brief cleanup SDK storage, this is for testing only
 */
+ (void) cleanup;

#pragma mark - track API
/*!
 *  @brief send customized track event to CrystalExpress tracking server
 *
 *  @param type  string represet event type
 *  @param props properties dictionary
 */
+ (void) trackCustomEventWithType:(NSString *)type props:(NSDictionary *)props;


/*!
 *  @brief get stream AD serving frequency server setting
 *
 *  @param placement placement string
 *
 *  @return int value for frequency number
 */
+ (int) getStreamADServingFreqWithPlacement:(NSString *)placement;

/*!
 *  @brief get stream AD serving min position server setting
 *
 *  @param placement placement string
 *
 *  @return int value for min position
 */
+ (int) getStreamADServingMinPositionWithPlacement:(NSString *)placement;

/*!
 *  @brief get stream AD serving max position server setting
 *
 *  @param placement placement string
 *
 *  @return int value for max position
 */
+ (int) getStreamADServingMaxPositionWithPlacement:(NSString *)placement;

#pragma mark - Ad tag
/*!
 *  @brief get AD placement name from (adTag name, position)
 *
 *  @param adTag    AD tag name
 *  @param posIndex position index to place AD
 *
 *  @return placement name
 */
+ (NSString *) getPlacementWithAdTag:(NSString *)adTag posIndex:(int)posIndex;

/*!
 *  @brief check whether this placement is blocking
 *
 *  @param placement placement name
 *
 *  @return true if placement group is blocking, otherwise false
 */
+ (BOOL) isPlacementBlocking:(NSString *)placement;

/*!
 *  @brief get stream placement setting, including acceptanceRanges, freq
 *
 *  @param tagName   ad tag name
 *  @param placement placement name
 *
 *  @return dictionary with info key: acceptanceRanges, freq
 */
+ (NSDictionary *) getPositionLimitationWithTagName:(NSString *)tagName placement:(NSString *)placement;

/*!
 *  @brief get stream all placements info, including min/max position in all placements, and placements name
 *
 *  @param tagName ad tag name
 *
 *  @return dictionary with info key: maxPos, minPos, placements
 */
+ (NSDictionary *) getStreamPlacementsInfoWithTagName:(NSString *)tagName;


/*!
 *  @brief refresh/remove unnecessary AD creatives
 */
+ (void) refreshI2WAds;


/*!
 *  @brief request stream AD
 *
 *  @param placement placement string
 *  @param helperKey the key to identify this request, will be placement+unix_timestamp (ex. STREAM_1435318372000)
 *  @param place     AD order
 *  @param adWidth   preferred stream AD width
 *  @param timeout   timeout second to wait for stream ad
 *  @param ready     callback block while ADView is ready
 *  @param failure   callback block while fail to request AD
 *  @param animation callback block while AD animation occur (ex. CARD-VIDEO-PULLDOWN AD is clicked by user)
 */
+ (void) getStreamADWithPlacement:(NSString *)placement
                        helperKey:(NSString *)helperKey
                            place:(int)place
                          adWidth:(CGFloat)adWidth
                          timeout:(int)timeout
                          onReady:(void (^)(ADView * adView))ready
                        onFailure:(void (^)(NSError * error))failure
              onPullDownAnimation:(void (^)(UIView *))animation;
@end
