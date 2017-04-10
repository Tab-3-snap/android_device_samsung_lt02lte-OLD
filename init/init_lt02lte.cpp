/*
   Copyright (c) 2013, The Linux Foundation. All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of The Linux Foundation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.
   THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
   ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
   BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
   BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdlib.h>

#include "vendor_init.h"
#include "property_service.h"
#include "util.h"

#define DEVICE_NAME "lt02"

void common_properties()
{
    property_set("rild.libpath", "/system/lib/libsec-ril.so");
    property_set("rild.libargs", "-d /dev/smd0");
}

void cdma_properties(char const default_cdma_sub[], char const default_network[])
{
    property_set("ro.telephony.default_cdma_sub", default_cdma_sub);
    property_set("ro.telephony.default_network", default_network);
    property_set("telephony.lteOnCdmaDevice", "1");
}

void gsm_properties(char const default_network[])
{
    property_set("ro.telephony.default_network", default_network);
    property_set("telephony.lteOnGsmDevice", "1");
}

static void set_device(const char *radio,
		       const char *region,
		       const char *model)
{
	char device[16], name[16];

	sprintf(device, "%s%s", DEVICE_NAME, radio);
	sprintf(name, "%s%s", device, region);

	property_set("ro.product.name", name);
	property_set("ro.product.device", device);
	property_set("ro.product.model", model);
}

void vendor_load_properties()
{
	char bootloader[PROP_VALUE_MAX];

	property_get("ro.bootloader", bootloader);

	if (strstr(bootloader, "T217S")) {
		/* Sprint */
		common_properties();
		cdma_properties("1", "8");
		set_device("lte", "spr", "SM-T217S");
		property_set("ro.build.fingerprint", "samsung/lt02ltespr/lt02ltespr:4.4.2/KOT49H/T217SVPSBQA1:user/release-keys");
		property_set("ro.build.description", "lt02ltespr-user 4.4.2 KOT49H T217SVPSBQA1 release-keys");
	} else if (strstr(bootloader, "T217T")) {
		/* T-Mobile */
		gsm_properties("3");
		set_device("lte", "tmo", "SM-T217T");
		property_set("ro.build.fingerprint", "samsung/lt02ltetmo/lt02ltetmo:4.4.2/KOT49H/T217TVPUBOH1:user/release-keys");
		property_set("ro.build.description", "lt02ltetmo-user 4.4.2 KOT49H T217TVPUBOH1 release-keys");
	}
}
