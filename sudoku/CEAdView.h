/*!
 * @header CEADView.h
 *
 * @brief AD View control
 *
 * @author Intowow
 * @copyright 2016 intowow. All rights reserved.
 */

#ifndef crystalexpress_CEADView_h
#define crystalexpress_CEADView_h

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

/*!
 *  @brief ADView class interface
 */
@interface ADView : UIView
/*!
 *  @brief call onShow while ADView is seen by user
 */
- (void) onShow;

/*!
 *  @brief call onHide while ADView is hide from user
 */
- (void) onHide;

/*!
 *  @brief call onStart to trigger ADView impression and video play
 */
- (void) onStart;

/*!
 *  @brief call onStop to stop ADView video play
 */
- (void) onStop;

@end
#endif /* ifndef crystalexpress_CEADView_h */
