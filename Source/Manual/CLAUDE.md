[Root Directory](../../../CLAUDE.md) > [Source](../) > **Manual**

# Manual Module Documentation

## Module Responsibilities

The Manual module demonstrates hand-crafted Unreal Engine module creation, showcasing complete control over module structure and implementation. It serves as a comprehensive example of inter-module dependencies by consuming classes from the Auto module, and provides a full spectrum of class types: Blueprint-accessible, C++-only, and internal implementation classes.

## Entry and Startup

### Module Interface
- **Class**: `FManualModule`
- **Header**: `Source/Manual/Public/ManualModule.h`
- **Implementation**: `Source/Manual/Private/ManualModule.cpp`
- **Loading Phase**: Default
- **Type**: Runtime
- **API Export**: `MANUAL_API`

### Startup Sequence
```cpp
void FManualModule::StartupModule()
{
    UE_LOG(LogManual, Warning, TEXT("FManualModule::StartupModule()"));
}
```

### Logging Configuration
The module defines its own log category for debugging and monitoring:
```cpp
DECLARE_LOG_CATEGORY_EXTERN(LogManual, Log, All);
DEFINE_LOG_CATEGORY(LogManual);
```

## External Interfaces

### Blueprint-Accessible Classes

#### AManualExposed
- **Header**: `Source/Manual/Public/ManualExposed.h`
- **Purpose**: Primary Blueprint-C++ integration point
- **Inheritance**: `AActor`
- **Inter-module Usage**: Demonstrates consumption of Auto module's `FAutoCppOnly`

**Key Features:**
- Blueprintable for direct inheritance in Blueprint
- Contains `FAutoCppOnly` member from Auto module
- Provides BlueprintCallable function that triggers inter-module communication

```cpp
UCLASS(Blueprintable)
class MANUAL_API AManualExposed : public AActor
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Manual")
    void DoManualExposed() const;

    FAutoCppOnly AutoCppOnly;  // Inter-module dependency
};
```

**Implementation Pattern:**
```cpp
void AManualExposed::DoManualExposed() const
{
    UE_LOG(LogManual, Warning, TEXT("AManualExposed::DoManualExposed()"));
    AutoCppOnly.DoAutoCppOnly();  // Calls Auto module function
}
```

### C++-Only Classes

#### FManualCppOnly
- **Header**: `Source/Manual/Public/ManualCppOnly.h`
- **Purpose**: High-performance C++ API without Blueprint overhead
- **Access**: C++ modules only
- **Performance**: No reflection system overhead

```cpp
class MANUAL_API FManualCppOnly
{
public:
    FManualCppOnly();
    void DoManualCppOnly();
};
```

## Key Dependencies and Configuration

### Build Configuration
- **File**: `Source/Manual/Manual.Build.cs`
- **Inter-module Dependency**: Explicitly depends on Auto module
- **PCH Usage**: UseExplicitOrSharedPCHs

### Public Dependencies
- `Core` - Essential UE core functionality  
- `Auto` - **Inter-module dependency** demonstrating module consumption

### Private Dependencies
- `CoreUObject` - UObject system support
- `Engine` - Core engine functionality

### Dependency Declaration
```csharp
PublicDependencyModuleNames.AddRange([
    "Core",
    "Auto"  // Enables use of Auto module classes
]);
```

This dependency structure allows Manual module to:
- Include headers from Auto module's Public folder
- Link against Auto module's compiled code
- Use Auto module's exported API classes

## Data Models

### Inter-Module Communication Pattern

The Manual module demonstrates proper inter-module usage:

```cpp
// ManualExposed.h - Including external module header
#include "AutoCppOnly.h"

// Class definition with external dependency
class MANUAL_API AManualExposed : public AActor
{
    FAutoCppOnly AutoCppOnly;  // Member from external module
};

// ManualExposed.cpp - Using external module functionality
void AManualExposed::DoManualExposed() const
{
    AutoCppOnly.DoAutoCppOnly();  // Cross-module function call
}
```

### Internal Implementation

#### FManualInternal
- **Header**: `Source/Manual/Private/ManualInternal.h`
- **Purpose**: Module-private implementation details
- **Access**: Internal to Manual module only (no API export)

```cpp
class FManualInternal  // No API macro - private to module
{
    FManualInternal();
    void DoManualInternal() const;
};
```

## Testing and Quality

### Inter-Module Integration Testing
- **Dependency Resolution**: Auto module classes successfully included and linked
- **Runtime Communication**: `FAutoCppOnly` methods called correctly from Manual module
- **Build System**: Module dependency chain resolves properly during compilation

### Blueprint Integration Testing
- `AManualExposed` appears in Blueprint class browser
- Blueprint inheritance from `AManualExposed` works correctly
- `DoManualExposed()` function callable from Blueprint graphs
- Blueprint asset `Content/Manual/BP_ManualExposed.uasset` created successfully

### Constructor Behavior
The module handles UE's multiple constructor calls properly:
```cpp
AManualExposed::AManualExposed()
{
    UE_LOG(LogManual, Warning, TEXT("AManualExposed::AManualExposed()"));
    // Lightweight constructor - UE calls this multiple times for CDO, validation, etc.
}
```

### Module Loading Verification
Expected log output during engine startup:
```
LogManual: Warning: FManualModule::StartupModule()
LogManual: Warning: AManualExposed::AManualExposed()  // May appear multiple times
```

## FAQ

### Q: Why does Manual depend on Auto instead of the reverse?
A: This is purely for demonstration. In real projects, dependency direction should reflect actual architectural needs, not creation methodology.

### Q: Why are there multiple constructor calls?
A: UE calls constructors for CDO (Class Default Object), Blueprint validation, editor preview, and actual instance creation. This is normal behavior.

### Q: Can I use Manual module classes in other modules?
A: Yes, add "Manual" to the target module's `PublicDependencyModuleNames` and include the appropriate headers.

### Q: What's the purpose of the MANUAL_API macro?
A: It exports symbols for use by other modules and ensures proper DLL linkage on Windows platforms.

## Related Files

### Core Module Files
- `Manual.Build.cs` - Build configuration with Auto dependency
- `ManualModule.h/.cpp` - Module interface and logging setup
- `ManualExposed.h/.cpp` - Blueprint-accessible class with inter-module usage
- `ManualCppOnly.h/.cpp` - C++-only performance class
- `ManualInternal.h/.cpp` - Private implementation details

### Blueprint Assets
- `Content/Manual/BP_ManualExposed.uasset` - Blueprint class derived from `AManualExposed`

### Generated Files
- `ManualExposed.generated.h` - UE reflection system generated code

### Configuration References
- Listed in `FirstModule.uproject` module configuration
- Registered in Game and Editor target files
- Auto dependency declared in Build.cs enables cross-module functionality

## Changelog

**2025-09-26 10:55:07** - Initial documentation creation
- Documented manual module creation process
- Analyzed inter-module dependency patterns with Auto module
- Verified Blueprint integration and C++ class organization
- Established testing patterns for cross-module communication