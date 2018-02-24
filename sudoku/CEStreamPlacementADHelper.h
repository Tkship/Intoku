//
//  CEStreamPlacementADHelper.h
//  crystalexpress
//
//  Copyright © 2015 intowow. All rights reserved.
//

#import "CEStreamTagADHelper.h"

@interface CEStreamPlacementADHelper : CEStreamTagADHelper

- (instancetype) initWithPlacement:(NSString *)placement delegate:(id<CEStreamAdHelperDelegate>)delegate;
@end
