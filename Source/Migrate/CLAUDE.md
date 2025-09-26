[Root Directory](../../../CLAUDE.md) > [Source](../) > **Migrate**

# Migrate Module Documentation

## Module Responsibilities

The Migrate module serves as a practical demonstration of module migration from external projects into existing Unreal Engine codebases. It showcases the process of integrating pre-existing module code, maintaining compatibility across different project structures, and handling potential API differences during the migration process.

## Entry and Startup

### Module Interface
- **Class**: `FMigrateModule`
- **Header**: `Source/Migrate/Public/Migrate.h`
- **Implementation**: `Source/Migrate/Private/Migrate.cpp`
- **Loading Phase**: Default
- **Type**: Runtime
- **API Export**: `MIGRATE_API`

### Startup Sequence
```cpp
void FMigrateModule::StartupModule()
{
    // Module initialization logic
}

void FMigrateModule::ShutdownModule()
{
    // Module cleanup logic
}
```

### Module Registration
```cpp
IMPLEMENT_MODULE(FMigrateModule, Migrate)
```

## External Interfaces

### Actor Classes

#### AMigrateActor
- **Header**: `Source/Migrate/Public/MigrateActor.h`
- **Purpose**: Standard UE Actor demonstrating migrated gameplay functionality
- **Inheritance**: `AActor`
- **Capabilities**: Standard Actor lifecycle with potential for Blueprint extension

**Class Structure:**
```cpp
UCLASS()
class MIGRATE_API AMigrateActor : public AActor
{
    GENERATED_BODY()

public:
    AMigrateActor();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;
};
```

**Implementation Pattern:**
```cpp
AMigrateActor::AMigrateActor()
{
    PrimaryActorTick.bCanEverTick = true;
    // Constructor logs demonstrate successful migration
}

void AMigrateActor::BeginPlay()
{
    Super::BeginPlay();
    // Game logic initialization
}

void AMigrateActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    // Per-frame update logic
}
```

## Key Dependencies and Configuration

### Build Configuration
- **File**: `Source/Migrate/Migrate.Build.cs`
- **Build Rules**: Uses legacy array syntax for broader compatibility
- **PCH Usage**: UseExplicitOrSharedPCHs

### Public Dependencies
- `Core` - Essential UE core functionality

### Private Dependencies
- `CoreUObject` - UObject system support
- `Engine` - Core engine functionality  
- `Slate` - UI framework support
- `SlateCore` - Core UI functionality

### Legacy Compatibility
The module uses older UE syntax patterns for maximum compatibility:
```csharp
PublicDependencyModuleNames.AddRange(
    new string[]
    {
        "Core",
    }
);

PrivateDependencyModuleNames.AddRange(
    new string[]
    {
        "CoreUObject",
        "Engine",
        "Slate",
        "SlateCore"
    }
);
```

## Data Models

### Actor Lifecycle Management

The `AMigrateActor` follows standard UE Actor patterns:

```cpp
class MIGRATE_API AMigrateActor : public AActor
{
    // Standard Actor interface
    // Compatible with existing UE systems
    // Maintains migration source compatibility
};
```

### Migration Considerations

**API Compatibility:**
- Uses standard UE macro patterns (`UCLASS`, `GENERATED_BODY`)
- Maintains compatibility with UE 5.6 reflection system
- Follows established Actor lifecycle patterns

**Build System Integration:**
- Module builds correctly with legacy and modern syntax
- Dependencies resolve properly in target project
- No circular dependency issues introduced

## Testing and Quality

### Migration Verification
- **Build System**: Module compiles successfully in target project
- **Runtime Loading**: Module loads without errors during engine startup
- **Actor Instantiation**: `AMigrateActor` can be created and placed in levels
- **Lifecycle Testing**: Actor lifecycle methods execute correctly

### Integration Testing
- No conflicts with existing modules (FirstModule, Auto, Manual)
- Build dependencies resolve correctly
- Project generation includes migrated module appropriately

### Migration Log Verification
Expected output confirming successful migration:
```
LogTemp: Warning: MigrateActor::AMigrateActor
```

### Compatibility Testing
- Works with both Game and Editor configurations
- Compatible with existing project settings
- No API conflicts with target project modules

## Migration Process Documentation

### Source Project Requirements
- Module should be self-contained with minimal external dependencies
- Build.cs file should use compatible UE build system patterns
- Public interfaces should use appropriate API export macros

### Target Project Integration
1. **File Copy**: Copy entire module folder to target `Source/` directory
2. **Project Configuration**: Add module to `.uproject` file
3. **Build Configuration**: Update Target.cs files to include module
4. **Regeneration**: Generate project files and build

### Post-Migration Verification
- Verify module appears in module list
- Check for compilation errors or warnings
- Test basic functionality to ensure proper integration
- Validate that no existing functionality is broken

## FAQ

### Q: What makes a module "migratable"?
A: Self-contained modules with clear dependencies and standard UE patterns migrate most easily.

### Q: Can migrated modules depend on target project modules?
A: Yes, but dependencies should be updated in the Build.cs file after migration.

### Q: Why does this module include Slate dependencies?
A: The source project likely had UI functionality, demonstrating dependency preservation during migration.

### Q: How do I handle version compatibility issues?
A: Update deprecated API calls, verify Build.cs syntax, and test thoroughly in the target UE version.

## Migration Best Practices

### Do's
- Keep modules self-contained with minimal external dependencies
- Use standard UE API export patterns (`MODULE_API` macros)
- Maintain clear dependency hierarchies
- Test thoroughly after migration
- Document any API changes required

### Don'ts
- Don't migrate system-generated files (Intermediate/, Binaries/)
- Don't assume all dependencies exist in target project
- Don't skip project file regeneration
- Don't modify core migration files without backup

## Related Files

### Core Module Files
- `Migrate.Build.cs` - Build configuration with UI dependencies
- `Migrate.h/.cpp` - Module interface implementation
- `MigrateActor.h/.cpp` - Example Actor class demonstrating migration

### Configuration Integration
- Added to `FirstModule.uproject` module list
- Registered in `FirstModule.Target.cs` and `FirstModuleEditor.Target.cs`
- Included in project build system

### Migration Source
- Represents typical module structure from external UE project
- Demonstrates successful integration with existing codebase
- Maintains original functionality while adapting to new environment

## Changelog

**2025-09-26 10:55:07** - Initial documentation creation
- Analyzed migrated module structure and dependencies
- Documented integration with existing project architecture
- Verified successful migration and runtime functionality
- Established migration process documentation and best practices