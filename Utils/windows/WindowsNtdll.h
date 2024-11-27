#pragma once
#include "WindowsDef.h"

// enums define
namespace utils {
    namespace windows {
        namespace ntdll {
            enum SYSTEM_INFORMATION_CLASS {
                SystemBasicInformation = 0x00,
                SystemProcessorInformation = 0x01,
                SystemPerformanceInformation = 0x02,
                SystemTimeOfDayInformation = 0x03,
                SystemPathInformation = 0x04,
                SystemProcessInformation = 0x05,
                SystemCallCountInformation = 0x06,
                SystemDeviceInformation = 0x07,
                SystemProcessorPerformanceInformation = 0x08,
                SystemFlagsInformation = 0x09,
                SystemCallTimeInformation = 0x0A,
                SystemModuleInformation = 0x0B,
                SystemLocksInformation = 0x0C,
                SystemStackTraceInformation = 0x0D,
                SystemPagedPoolInformation = 0x0E,
                SystemNonPagedPoolInformation = 0x0F,
                SystemHandleInformation = 0x10,
                SystemObjectInformation = 0x11,
                SystemPageFileInformation = 0x12,
                SystemVdmInstemulInformation = 0x13,
                SystemFileCacheInformation = 0x15,
                SystemPoolTagInformation = 0x16,
                SystemInterruptInformation = 0x17,
                SystemDpcBehaviorInformation = 0x18,
                SystemFullMemoryInformation = 0x19,
                SystemTimeAdjustmentInformation = 0x1C,
                SystemSummaryMemoryInformation = 0x1D,
                SystemNextEventIdInformation = 0x1E,
                SystemEventIdsInformation = 0x1F,
                SystemCrashDumpInformation = 0x20,
                SystemExceptionInformation = 0x21,
                SystemCrashDumpStateInformation = 0x22,
                SystemKernelDebuggerInformation = 0x23,
                SystemContextSwitchInformation = 0x24,
                SystemRegistryQuotaInformation = 0x25,
                SystemPlugPlayBusInformation = 0x28,
                SystemDockInformation = 0x29,
                SystemProcessorIdleInformation = 0x2A,
                SystemLegacyDriverInformation = 0x2B,
                SystemCurrentTimeZoneInformation = 0x2C,
                SystemLookasideInformation = 0x2D,
                SystemRangeStartInformation = 0x32,
                SystemVerifierInformation = 0x33,
                SystemSessionProcessInformation = 0x35,
                SystemPrefetcherInformation = 0x38,
                SystemExtendedProcessInformation = 0x39,
                SystemRecommendedSharedDataAlignment = 0x3A,
                SystemComPlusPackage = 0x3B,
                SystemNumaAvailableMemory = 0x3C,
                SystemProcessorPowerInformation = 0x3D,
                SystemEmulationBasicInformation = 0x3E,
                SystemEmulationProcessorInformation = 0x3F,
                SystemExtendedHandleInformation = 0x40,
                SystemLostDelayedWriteInformation = 0x41,
                SystemSessionPoolTagInformation = 0x43,
                SystemSessionMappedViewInformation = 0x44,
                SystemHotpatchInformation = 0x45,
                SystemWatchdogTimerInformation = 0x48,
                SystemLogicalProcessorInformation = 0x49,
                SystemFirmwareTableInformation = 0x4C,
                SystemModuleInformationEx = 0x4D,
                SystemSuperfetchInformation = 0x4F,
                SystemMemoryListInformation = 0x50,
                SystemFileCacheInformationEx = 0x51,
                SystemProcessorIdleCycleTimeInformation = 0x53,
                SystemVerifierCancellationInformation = 0x54,
                SystemRefTraceInformation = 0x56,
                SystemSpecialPoolInformation = 0x57,
                SystemProcessIdInformation = 0x58,
                SystemBootEnvironmentInformation = 0x5A,
                SystemHypervisorInformation = 0x5B,
                SystemVerifierInformationEx = 0x5C,
                SystemCoverageInformation = 0x5F,
                SystemPrefetchPatchInformation = 0x60,
                SystemSystemPartitionInformation = 0x62,
                SystemSystemDiskInformation = 0x63,
                SystemProcessorPerformanceDistribution = 0x64,
                SystemNumaProximityNodeInformation = 0x65,
                SystemDynamicTimeZoneInformation = 0x66,
                SystemCodeIntegrityInformation = 0x67,
                SystemProcessorBrandString = 0x69,
                SystemVirtualAddressInformation = 0x6A,
                SystemProcessorCycleTimeInformation = 0x6C,
                SystemStoreInformation = 0x6D,
                SystemVhdBootInformation = 0x70,
                SystemCpuQuotaInformation = 0x71,
                SystemNativeBasicInformation = 0x72,
                SystemErrorPortTimeouts = 0x73,
                SystemLowPriorityIoInformation = 0x74,
                SystemBootEntropyInformation = 0x75,
                SystemVerifierCountersInformation = 0x76,
                SystemPagedPoolInformationEx = 0x77,
                SystemSystemPtesInformationEx = 0x78,
                SystemAcpiAuditInformation = 0x7A,
                SystemBasicPerformanceInformation = 0x7B,
                SystemQueryPerformanceCounterInformation = 0x7C,
                SystemSessionBigPoolInformation = 0x7D,
                SystemBootGraphicsInformation = 0x7E,
                SystemBadPageInformation = 0x80,
                SystemPlatformBinaryInformation = 0x85,
                SystemPolicyInformation = 0x86,
                SystemHypervisorProcessorCountInformation = 0x87,
                SystemDeviceDataInformation = 0x88,
                SystemDeviceDataEnumerationInformation = 0x89,
                SystemMemoryTopologyInformation = 0x8A,
                SystemMemoryChannelInformation = 0x8B,
                SystemBootLogoInformation = 0x8C,
                SystemProcessorPerformanceInformationEx = 0x8D,
                SystemSecureBootPolicyInformation = 0x8F,
                SystemPageFileInformationEx = 0x90,
                SystemSecureBootInformation = 0x91,
                SystemPortableWorkspaceEfiLauncherInformation = 0x93,
                SystemFullProcessInformation = 0x94,
                SystemKernelDebuggerInformationEx = 0x95,
                SystemBootMetadataInformation = 0x96,
                SystemSoftRebootInformation = 0x97,
                SystemOfflineDumpConfigInformation = 0x99,
                SystemProcessorFeaturesInformation = 0x9A,
                SystemEdidInformation = 0x9C,
                SystemManufacturingInformation = 0x9D,
                SystemEnergyEstimationConfigInformation = 0x9E,
                SystemHypervisorDetailInformation = 0x9F,
                SystemProcessorCycleStatsInformation = 0xA0,
                SystemTrustedPlatformModuleInformation = 0xA2,
                SystemKernelDebuggerFlags = 0xA3,
                SystemCodeIntegrityPolicyInformation = 0xA4,
                SystemIsolatedUserModeInformation = 0xA5,
                SystemHardwareSecurityTestInterfaceResultsInformation = 0xA6,
                SystemSingleModuleInformation = 0xA7,
                SystemDmaProtectionInformation = 0xA9,
                SystemSecureBootPolicyFullInformation = 0xAB,
                SystemCodeIntegrityPolicyFullInformation = 0xAC,
                SystemAffinitizedInterruptProcessorInformation = 0xAD,
                SystemRootSiloInformation = 0xAE,
                SystemCpuSetInformation = 0xAF,
                SystemSecureKernelProfileInformation = 0xB2,
                SystemCodeIntegrityPlatformManifestInformation = 0xB3,
                SystemInterruptSteeringInformation = 0xB4,
                SystemSupportedProcessorArchitectures = 0xB5,
                SystemMemoryUsageInformation = 0xB6,
                SystemCodeIntegrityCertificateInformation = 0xB7,
                SystemPhysicalMemoryInformation = 0xB8,
                SystemControlFlowTransition = 0xB9,
                SystemKernelDebuggingAllowed = 0xBA,
                SystemActivityModerationUserSettings = 0xBC,
                SystemCodeIntegrityPoliciesFullInformation = 0xBD,
                SystemCodeIntegrityUnlockInformation = 0xBE,
                SystemFlushInformation = 0xC0,
                SystemProcessorIdleMaskInformation = 0xC1,
                SystemWriteConstraintInformation = 0xC3,
                SystemKernelVaShadowInformation = 0xC4,
                SystemHypervisorSharedPageInformation = 0xC5,
                SystemFirmwareBootPerformanceInformation = 0xC6,
                SystemCodeIntegrityVerificationInformation = 0xC7,
                SystemFirmwarePartitionInformation = 0xC8,
                SystemSpeculationControlInformation = 0xC9,
                SystemDmaGuardPolicyInformation = 0xCA,
            };

            enum OBJECT_INFORMATION_CLASS {
                ObjectBasicInformation = 0,
                ObjectNameInformation = 1,
                ObjectTypeInformation = 2,
                ObjectTypesInformation = 3,
                ObjectHandleFlagInformation = 4,
                ObjectSessionInformation = 5,
                ObjectSessionObjectInformation = 6,
                MaxObjectInfoClass = 7,
            };

            enum POOL_TYPE {
                NonPagedPool,
                PagedPool,
                NonPagedPoolMustSucceed,
                DontUseThisType,
                NonPagedPoolCacheAligned,
                PagedPoolCacheAligned,
                NonPagedPoolCacheAlignedMustS
            };

            enum PROCESSINFOCLASS {
                ProcessBasicInformation,           // q: PROCESS_BASIC_INFORMATION, PROCESS_EXTENDED_BASIC_INFORMATION
                ProcessQuotaLimits,                // qs: QUOTA_LIMITS, QUOTA_LIMITS_EX
                ProcessIoCounters,                 // q: IO_COUNTERS
                ProcessVmCounters,                 // q: VM_COUNTERS, VM_COUNTERS_EX, VM_COUNTERS_EX2
                ProcessTimes,                      // q: KERNEL_USER_TIMES
                ProcessBasePriority,               // s: KPRIORITY
                ProcessRaisePriority,              // s: ULONG
                ProcessDebugPort,                  // q: HANDLE
                ProcessExceptionPort,              // s: PROCESS_EXCEPTION_PORT (requires SeTcbPrivilege)
                ProcessAccessToken,                // s: PROCESS_ACCESS_TOKEN
                ProcessLdtInformation,             // qs: PROCESS_LDT_INFORMATION // 10
                ProcessLdtSize,                    // s: PROCESS_LDT_SIZE
                ProcessDefaultHardErrorMode,       // qs: ULONG
                ProcessIoPortHandlers,             // (kernel-mode only) // s: PROCESS_IO_PORT_HANDLER_INFORMATION
                ProcessPooledUsageAndLimits,       // q: POOLED_USAGE_AND_LIMITS
                ProcessWorkingSetWatch,            // q: PROCESS_WS_WATCH_INFORMATION[]; s: void
                ProcessUserModeIOPL,               // qs: ULONG (requires SeTcbPrivilege)
                ProcessEnableAlignmentFaultFixup,  // s: BOOLEAN
                ProcessPriorityClass,              // qs: PROCESS_PRIORITY_CLASS
                ProcessWx86Information,            // qs: ULONG (requires SeTcbPrivilege) (VdmAllowed)
                ProcessHandleCount,                // q: ULONG, PROCESS_HANDLE_INFORMATION // 20
                ProcessAffinityMask,               // (q >WIN7)s: KAFFINITY, qs: GROUP_AFFINITY
                ProcessPriorityBoost,              // qs: ULONG
                ProcessDeviceMap,              // qs: PROCESS_DEVICEMAP_INFORMATION, PROCESS_DEVICEMAP_INFORMATION_EX
                ProcessSessionInformation,     // q: PROCESS_SESSION_INFORMATION
                ProcessForegroundInformation,  // s: PROCESS_FOREGROUND_BACKGROUND
                ProcessWow64Information,       // q: ULONG_PTR
                ProcessImageFileName,          // q: UNICODE_STRING
                ProcessLUIDDeviceMapsEnabled,  // q: ULONG
                ProcessBreakOnTermination,     // qs: ULONG
                ProcessDebugObjectHandle,      // q: HANDLE // 30
                ProcessDebugFlags,             // qs: ULONG
                ProcessHandleTracing,  // q: PROCESS_HANDLE_TRACING_QUERY; s: PROCESS_HANDLE_TRACING_ENABLE[_EX] or void to disable
                ProcessIoPriority,               // qs: IO_PRIORITY_HINT
                ProcessExecuteFlags,             // qs: ULONG (MEM_EXECUTE_OPTION_*)
                ProcessTlsInformation,           // PROCESS_TLS_INFORMATION // ProcessResourceManagement
                ProcessCookie,                   // q: ULONG
                ProcessImageInformation,         // q: SECTION_IMAGE_INFORMATION
                ProcessCycleTime,                // q: PROCESS_CYCLE_TIME_INFORMATION // since VISTA
                ProcessPagePriority,             // qs: PAGE_PRIORITY_INFORMATION
                ProcessInstrumentationCallback,  // s: PVOID or PROCESS_INSTRUMENTATION_CALLBACK_INFORMATION // 40
                ProcessThreadStackAllocation,  // s: PROCESS_STACK_ALLOCATION_INFORMATION, PROCESS_STACK_ALLOCATION_INFORMATION_EX
                ProcessWorkingSetWatchEx,                // q: PROCESS_WS_WATCH_INFORMATION_EX[]; s: void
                ProcessImageFileNameWin32,               // q: UNICODE_STRING
                ProcessImageFileMapping,                 // q: HANDLE (input)
                ProcessAffinityUpdateMode,               // qs: PROCESS_AFFINITY_UPDATE_MODE
                ProcessMemoryAllocationMode,             // qs: PROCESS_MEMORY_ALLOCATION_MODE
                ProcessGroupInformation,                 // q: USHORT[]
                ProcessTokenVirtualizationEnabled,       // s: ULONG
                ProcessConsoleHostProcess,               // qs: ULONG_PTR // ProcessOwnerInformation
                ProcessWindowInformation,                // q: PROCESS_WINDOW_INFORMATION // 50
                ProcessHandleInformation,                // q: PROCESS_HANDLE_SNAPSHOT_INFORMATION // since WIN8
                ProcessMitigationPolicy,                 // s: PROCESS_MITIGATION_POLICY_INFORMATION
                ProcessDynamicFunctionTableInformation,  // s: PROCESS_DYNAMIC_FUNCTION_TABLE_INFORMATION
                ProcessHandleCheckingMode,               // qs: ULONG; s: 0 disables, otherwise enables
                ProcessKeepAliveCount,                   // q: PROCESS_KEEPALIVE_COUNT_INFORMATION
                ProcessRevokeFileHandles,                // s: PROCESS_REVOKE_FILE_HANDLES_INFORMATION
                ProcessWorkingSetControl,                // s: PROCESS_WORKING_SET_CONTROL (requires SeDebugPrivilege)
                ProcessHandleTable,                      // q: ULONG[] // since WINBLUE
                ProcessCheckStackExtentsMode,            // qs: ULONG // KPROCESS->CheckStackExtents (CFG)
                ProcessCommandLineInformation,           // q: UNICODE_STRING // 60
                ProcessProtectionInformation,            // q: PS_PROTECTION
                ProcessMemoryExhaustion,                 // s: PROCESS_MEMORY_EXHAUSTION_INFO // since THRESHOLD
                ProcessFaultInformation,                 // s: PROCESS_FAULT_INFORMATION
                ProcessTelemetryIdInformation,           // q: PROCESS_TELEMETRY_ID_INFORMATION
                ProcessCommitReleaseInformation,         // qs: PROCESS_COMMIT_RELEASE_INFORMATION
                ProcessDefaultCpuSetsInformation,        // qs: SYSTEM_CPU_SET_INFORMATION[5]
                ProcessAllowedCpuSetsInformation,        // qs: SYSTEM_CPU_SET_INFORMATION[5]
                ProcessSubsystemProcess,
                ProcessJobMemoryInformation,                  // q: PROCESS_JOB_MEMORY_INFO
                ProcessInPrivate,                             // q: BOOLEAN; s: void // ETW // since THRESHOLD2 // 70
                ProcessRaiseUMExceptionOnInvalidHandleClose,  // qs: ULONG; s: 0 disables, otherwise enables
                ProcessIumChallengeResponse,
                ProcessChildProcessInformation,          // q: PROCESS_CHILD_PROCESS_INFORMATION
                ProcessHighGraphicsPriorityInformation,  // qs: BOOLEAN (requires SeTcbPrivilege)
                ProcessSubsystemInformation,             // q: SUBSYSTEM_INFORMATION_TYPE // since REDSTONE2
                ProcessEnergyValues,                     // q: PROCESS_ENERGY_VALUES, PROCESS_EXTENDED_ENERGY_VALUES
                ProcessPowerThrottlingState,             // qs: POWER_THROTTLING_PROCESS_STATE
                ProcessReserved3Information,  // ProcessActivityThrottlePolicy // PROCESS_ACTIVITY_THROTTLE_POLICY
                ProcessWin32kSyscallFilterInformation,  // q: WIN32K_SYSCALL_FILTER
                ProcessDisableSystemAllowedCpuSets,     // s: BOOLEAN // 80
                ProcessWakeInformation,                 // q: PROCESS_WAKE_INFORMATION
                ProcessEnergyTrackingState,             // qs: PROCESS_ENERGY_TRACKING_STATE
                ProcessManageWritesToExecutableMemory,  // MANAGE_WRITES_TO_EXECUTABLE_MEMORY // since REDSTONE3
                ProcessCaptureTrustletLiveDump,
                ProcessTelemetryCoverage,  // q: TELEMETRY_COVERAGE_HEADER; s: TELEMETRY_COVERAGE_POINT
                ProcessEnclaveInformation,
                ProcessEnableReadWriteVmLogging,           // qs: PROCESS_READWRITEVM_LOGGING_INFORMATION
                ProcessUptimeInformation,                  // q: PROCESS_UPTIME_INFORMATION
                ProcessImageSection,                       // q: HANDLE
                ProcessDebugAuthInformation,               // since REDSTONE4 // 90
                ProcessSystemResourceManagement,           // s: PROCESS_SYSTEM_RESOURCE_MANAGEMENT
                ProcessSequenceNumber,                     // q: ULONGLONG
                ProcessLoaderDetour,                       // since REDSTONE5
                ProcessSecurityDomainInformation,          // q: PROCESS_SECURITY_DOMAIN_INFORMATION
                ProcessCombineSecurityDomainsInformation,  // s: PROCESS_COMBINE_SECURITY_DOMAINS_INFORMATION
                ProcessEnableLogging,                      // qs: PROCESS_LOGGING_INFORMATION
                ProcessLeapSecondInformation,              // qs: PROCESS_LEAP_SECOND_INFORMATION
                ProcessFiberShadowStackAllocation,  // s: PROCESS_FIBER_SHADOW_STACK_ALLOCATION_INFORMATION // since 19H1
                ProcessFreeFiberShadowStackAllocation,  // s: PROCESS_FREE_FIBER_SHADOW_STACK_ALLOCATION_INFORMATION
                ProcessAltSystemCallInformation,        // s: PROCESS_SYSCALL_PROVIDER_INFORMATION // since 20H1 // 100
                ProcessDynamicEHContinuationTargets,    // s: PROCESS_DYNAMIC_EH_CONTINUATION_TARGETS_INFORMATION
                ProcessDynamicEnforcedCetCompatibleRanges,  // s: PROCESS_DYNAMIC_ENFORCED_ADDRESS_RANGE_INFORMATION // since 20H2
                ProcessCreateStateChange,                   // since WIN11
                ProcessApplyStateChange,
                ProcessEnableOptionalXStateFeatures,  // s: ULONG64 // optional XState feature bitmask
                ProcessAltPrefetchParam,  // qs: OVERRIDE_PREFETCH_PARAMETER // App Launch Prefetch (ALPF) // since 22H1
                ProcessAssignCpuPartitions,    // HANDLE
                ProcessPriorityClassEx,        // s: PROCESS_PRIORITY_CLASS_EX
                ProcessMembershipInformation,  // q: PROCESS_MEMBERSHIP_INFORMATION
                ProcessEffectiveIoPriority,    // q: IO_PRIORITY_HINT // 110
                ProcessEffectivePagePriority,  // q: ULONG
                ProcessSchedulerSharedData,    // SCHEDULER_SHARED_DATA_SLOT_INFORMATION // since 24H2
                ProcessSlistRollbackInformation,
                ProcessNetworkIoCounters,          // q: PROCESS_NETWORK_COUNTERS
                ProcessFindFirstThreadByTebValue,  // PROCESS_TEB_VALUE_INFORMATION
                MaxProcessInfoClass
            };
        };  // namespace ntdll
    };  // namespace windows
};  // namespace utils

// structs define
namespace utils {
    namespace windows {
        namespace ntdll {
            typedef struct _UNICODE_STRING {
                USHORT Length;
                USHORT MaximumLength;
                PWSTR Buffer;
            } UNICODE_STRING, *PUNICODE_STRING;

            typedef struct _SYSTEM_PROCESS_ID_INFORMATION {
                HANDLE ProcessId;
                UNICODE_STRING ImageName;
            } SYSTEM_PROCESS_ID_INFORMATION, *PSYSTEM_PROCESS_ID_INFORMATION;

            typedef struct _SYSTEM_HANDLE {
                ULONG ProcessId;
                BYTE ObjectTypeNumber;
                BYTE Flags;
                USHORT Handle;
                PVOID Object;
                ACCESS_MASK GrantedAccess;
            } SYSTEM_HANDLE, *PSYSTEM_HANDLE;

            typedef struct _SYSTEM_HANDLE_INFORMATION {
                ULONG HandleCount;
                SYSTEM_HANDLE Handles[1];
            } SYSTEM_HANDLE_INFORMATION, *PSYSTEM_HANDLE_INFORMATION;

            typedef struct _OBJECT_TYPE_INFORMATION {
                UNICODE_STRING Name;
                ULONG TotalNumberOfObjects;
                ULONG TotalNumberOfHandles;
                ULONG TotalPagedPoolUsage;
                ULONG TotalNonPagedPoolUsage;
                ULONG TotalNamePoolUsage;
                ULONG TotalHandleTableUsage;
                ULONG HighWaterNumberOfObjects;
                ULONG HighWaterNumberOfHandles;
                ULONG HighWaterPagedPoolUsage;
                ULONG HighWaterNonPagedPoolUsage;
                ULONG HighWaterNamePoolUsage;
                ULONG HighWaterHandleTableUsage;
                ULONG InvalidAttributes;
                GENERIC_MAPPING GenericMapping;
                ULONG ValidAccess;
                BOOLEAN SecurityRequired;
                BOOLEAN MaintainHandleCount;
                USHORT MaintainTypeList;
                POOL_TYPE PoolType;
                ULONG PagedPoolUsage;
                ULONG NonPagedPoolUsage;
            } OBJECT_TYPE_INFORMATION, *POBJECT_TYPE_INFORMATION;

            typedef struct _SYSTEM_PROCESS_INFO {
                ULONG NextEntryOffset;
                ULONG NumberOfThreads;
                LARGE_INTEGER Reserved[3];
                LARGE_INTEGER CreateTime;
                LARGE_INTEGER UserTime;
                LARGE_INTEGER KernelTime;
                UNICODE_STRING ImageName;
                ULONG BasePriority;
                HANDLE ProcessId;
                HANDLE InheritedFromProcessId;
            } SYSTEM_PROCESS_INFO, *PSYSTEM_PROCESS_INFO;

            typedef struct _OBJECT_ATTRIBUTES {
                ULONG Length;
                HANDLE RootDirectory;
                PUNICODE_STRING ObjectName;
                ULONG Attributes;
                PVOID SecurityDescriptor;
                PVOID SecurityQualityOfService;
            } OBJECT_ATTRIBUTES, *POBJECT_ATTRIBUTES;

            typedef struct _IO_STATUS_BLOCK {
                union {
                    NTSTATUS Status;
                    PVOID Pointer;
                };
                ULONG_PTR Information;
            } IO_STATUS_BLOCK, *PIO_STATUS_BLOCK;
        };  // namespace ntdll
    };  // namespace windows
};  // namespace utils

// functions define
namespace utils {
    namespace windows {
        namespace ntdll {
            NTSTATUS Load();
            NTSTATUS QuerySystemInformation(
                _In_ SYSTEM_INFORMATION_CLASS SystemInformationClass,
                _Inout_ PVOID SystemInformation,
                _In_ ULONG SystemInformationLength,
                _Out_opt_ PULONG ReturnLength
            );
            NTSTATUS DuplicateObject(
                _In_ HANDLE SourceProcessHandle,
                _In_ HANDLE SourceHandle,
                _In_opt_ HANDLE TargetProcessHandle,
                _Out_opt_ PHANDLE TargetHandle,
                _In_ ACCESS_MASK DesiredAccess,
                _In_ ULONG HandleAttributes,
                _In_ ULONG Options
            );
            NTSTATUS QueryObject(
                _In_opt_ HANDLE Handle,
                _In_ OBJECT_INFORMATION_CLASS ObjectInformationClass,
                _Out_opt_ PVOID ObjectInformation,
                _In_ ULONG ObjectInformationLength,
                _Out_opt_ PULONG ReturnLength
            );
            NTSTATUS QueryInformationProcess(
                _In_ HANDLE ProcessHandle,
                _In_ PROCESSINFOCLASS ProcessInformationClass,
                _Out_ PVOID ProcessInformation,
                _In_ ULONG ProcessInformationLength,
                _Out_opt_ PULONG ReturnLength
            );

            NTSTATUS CreateFile(
                _Out_ PHANDLE FileHandle,
                _In_ ACCESS_MASK DesiredAccess,
                _In_ POBJECT_ATTRIBUTES ObjectAttributes,
                _Out_ PIO_STATUS_BLOCK IoStatusBlock,
                _In_opt_ PLARGE_INTEGER AllocationSize,
                _In_ ULONG FileAttributes,
                _In_ ULONG ShareAccess,
                _In_ ULONG CreateDisposition,
                _In_ ULONG CreateOptions,
                _In_ PVOID EaBuffer,
                _In_ ULONG EaLength
            );

            VOID Initialize(POBJECT_ATTRIBUTES p, PUNICODE_STRING n, ULONG a, HANDLE r, PVOID s);

        };  // namespace ntdll
    };  // namespace windows
};  // namespace utils
