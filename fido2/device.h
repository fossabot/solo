/*
 * Copyright (C) 2018 SoloKeys, Inc. <https://solokeys.com/>
 * 
 * This file is part of Solo.
 * 
 * Solo is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Solo is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Solo.  If not, see <https://www.gnu.org/licenses/>
 * 
 * This code is available under licenses for commercial use.
 * Please contact SoloKeys for more information.
 */
#ifndef _DEVICE_H
#define _DEVICE_H

#include "storage.h"

void device_init();

uint32_t millis();

void delay(uint32_t ms);

// HID message size in bytes
#define HID_MESSAGE_SIZE        64

void usbhid_init();

int usbhid_recv(uint8_t * msg);

void usbhid_send(uint8_t * msg);

void usbhid_close();

void main_loop_delay();

void heartbeat();


void authenticator_read_state(AuthenticatorState * );

void authenticator_read_backup_state(AuthenticatorState * );

// Return 1 yes backup is init'd, else 0
//void authenticator_initialize()
int authenticator_is_backup_initialized();

void authenticator_write_state(AuthenticatorState *, int backup);

// Called each main loop.  Doesn't need to do anything.
void device_manage();

// sets status that's uses for sending status updates ~100ms.
// A timer should be set up to call `ctaphid_update_status`
void device_set_status(int status);

// Returns if button is currently pressed
int device_is_button_pressed();

// Test for user presence
// Return 1 for user is present, 0 user not present, -1 if cancel is requested.
extern int ctap_user_presence_test();

// Generate @num bytes of random numbers to @dest
// return 1 if success, error otherwise
extern int ctap_generate_rng(uint8_t * dst, size_t num);

// Increment atomic counter and return it.
// Must support two counters, @sel selects counter0 or counter1.
uint32_t ctap_atomic_count(int sel);

// Verify the user
// return 1 if user is verified, 0 if not
extern int ctap_user_verification(uint8_t arg);

// Must be implemented by application
// data is HID_MESSAGE_SIZE long in bytes
extern void ctaphid_write_block(uint8_t * data);


// Resident key
void ctap_reset_rk();
uint32_t ctap_rk_size();
void ctap_store_rk(int index,CTAP_residentKey * rk);
void ctap_load_rk(int index,CTAP_residentKey * rk);
void ctap_overwrite_rk(int index,CTAP_residentKey * rk);

// For Solo hacker
void boot_solo_bootloader();
void boot_st_bootloader();

// HID wink command
void device_wink();


#endif
