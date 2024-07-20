/*++

Module Name:

    public.h

Abstract:

    This module contains the common declarations shared by driver
    and user applications.

Environment:

    user and kernel

--*/

//
// Define an Interface Guid so that app can find the device and talk to it.
//

DEFINE_GUID (GUID_DEVINTERFACE_Kernel,
    0x5702fdcd,0x0bb2,0x4f2d,0x81,0xf4,0x2f,0x9f,0xfc,0xd0,0xf1,0x11);
// {5702fdcd-0bb2-4f2d-81f4-2f9ffcd0f111}
