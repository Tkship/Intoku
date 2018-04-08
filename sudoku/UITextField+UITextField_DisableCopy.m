//
//  UITextField+UITextField_DisableCopy.m
//  sudoku
//
//  Created by Hung Kuo xin on 2018/3/1.
//  Copyright © 2018年 Hung Kuo xin. All rights reserved.
//

#import "UITextField+UITextField_DisableCopy.h"

@implementation UITextField (UITextField_DisableCopy)

- (BOOL)canPerformAction:(SEL)action withSender:(id)sender {
    return NO;
}

@end
