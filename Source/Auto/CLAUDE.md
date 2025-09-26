[Root Directory](../../../CLAUDE.md) > [Source](../) > **Auto**

# Auto Module Documentation

## Module Responsibilities

The Auto module serves as a demonstration of IDE-generated Unreal Engine module creation, specifically using JetBrains Rider. It provides a baseline example of automated module scaffolding and showcases the standard patterns for C++ class organization in UE modules. The module includes both Blueprint-accessible and C++-only classes to demonstrate different exposure levels.

## Entry and Startup

### Module Interface
- **Class**: `FAutoModule`
- **Header**: `Source/Auto/Public/AutoModule.h`
- **Implementation**: `Source/Auto/Private/AutoModule.cpp`
- **Loading Phase**: Default
- **Type**: Runtime

### Startup Sequence
```cpp
void FAutoModule::StartupModule()
{
    UE_LOG(LogAuto, Warning, TEXT("FAutoModule::StartupModule()"));
}
```

The module registers itself using the standard UE pattern:
```cpp
IMPLEMENT_MODULE(FAutoModule, Auto)
```

## External Interfaces

### Blueprint-Accessible Classes

#### AAutoExposed
- **Header**: `Source/Auto/Public/AutoExposed.h`
- **Purpose**: Demonstrates Blueprint-C++ integration
- **Inheritance**: `AActor`
- **Capabilities**:
  - Blueprintable for inheritance
  - Contains BlueprintCallable function `DoAutoExposed()`
  - Can be instantiated directly in Blueprint

```cpp
UCLASS(Blueprintable)
class AUTO_API AAutoExposed : public AActor
{
    GENERATED_BODY()
    
public:
    UFUNCTION(BlueprintCallable, Category = "Auto")
    void DoAutoExposed() const;
};
```

### C++-Only Classes

#### FAutoCppOnly
- **Header**: `Source/Auto/Public/AutoCppOnly.h` 
- **Purpose**: High-performance C++ API for other modules
- **Access**: C++ modules only (no Blueprint access)
- **Usage**: Used by Manual module to demonstrate inter-module communication

```cpp
class AUTO_API FAutoCppOnly
{
public:
    FAutoCppOnly();
    void DoAutoCppOnly();
};
```

## Key Dependencies and Configuration

### Build Configuration
- **File**: `Source/Auto/Auto.Build.cs`
- **Type**: ModuleRules-derived class
- **PCH Usage**: UseExplicitOrSharedPCHs

### Public Dependencies
- `Core` - Essential UE core functionality

### Private Dependencies  
- `CoreUObject` - UObject system support
- `Engine` - Core engine functionality

### Module Registration
The module is registered in:
- `FirstModule.uproject` as Runtime module
- `FirstModule.Target.cs` via `RegisterModulesCreatedByRider()`
- `FirstModuleEditor.Target.cs` for editor builds

## Data Models

### FAutoCppOnly Structure
The module defines a simple C++ class that serves as a dependency target for other modules:

```cpp
class AUTO_API FAutoCppOnly
{
    // Standard C++ class with module API export
    // No UE reflection system involvement
    // Optimized for performance-critical operations
};
```

### AAutoExposed Actor
Blueprint-compatible actor demonstrating standard UE patterns:

```cpp
UCLASS(Blueprintable)
class AUTO_API AAutoExposed : public AActor
{
    GENERATED_BODY()
    // Uses UE reflection system
    // Supports Blueprint inheritance
    // Runtime type information available
};
```

## Testing and Quality

### Manual Testing
- Module loads successfully during engine startup
- `FAutoCppOnly` can be instantiated by dependent modules
- `AAutoExposed` appears in Blueprint class picker
- BlueprintCallable functions work correctly in Blueprint graphs

### Build Verification
- Compiles cleanly with no warnings in Development/Shipping configurations
- Generates correct API symbols for external module consumption
- Hot reload works correctly during development

### Dependency Testing
- Manual module successfully includes and uses `FAutoCppOnly`
- No circular dependency issues detected
- Module can be safely removed without breaking core functionality

## FAQ

### Q: Why is this module named "Auto"?
A: The name "Auto" refers to the automated creation process using JetBrains Rider, not any automatic functionality within the module.

### Q: Can other modules depend on Auto?
A: Yes, the Manual module demonstrates this by including Auto in its `PublicDependencyModuleNames` and using `FAutoCppOnly`.

### Q: What's the difference between Public and Private folders?
A: Public headers can be included by other modules, while Private files are internal implementation only.

### Q: Why use AUTO_API macro?
A: The API macro exports symbols for use by other modules on Windows platforms and ensures proper DLL linkage.

## Related Files

### Core Module Files
- `Auto.Build.cs` - Build configuration and dependencies
- `AutoModule.h/.cpp` - Module interface implementation
- `AutoExposed.h/.cpp` - Blueprint-accessible actor class
- `AutoCppOnly.h/.cpp` - C++-only utility class
- `AutoInternal.h/.cpp` - Private implementation details

### Generated Files
- `AutoExposed.generated.h` - UE reflection system generated code
- Build system generates appropriate `.obj` and `.lib` files

### Configuration References
- Referenced in `FirstModule.uproject` module list
- Included in both Game and Editor target configurations
- Dependencies declared in Manual module's Build.cs

## Changelog

**2025-09-26 10:55:07** - Initial documentation creation
- Analyzed IDE-generated module structure
- Documented public interfaces and dependencies
- Established Blueprint integration patterns
- Verified inter-module communication with Manual module