# GCI Calculator GUI

A cross-platform Qt-based graphical user interface for calculating the **Grid Convergence Index (GCI)**, based on the procedure presented by Celik et al. (2008). 

This application calculates:
- Grid refinement ratios ($r_{21}, r_{32}$)
- Apparent order of the method ($p$)
- Extrapolated values ($\phi_{ext}$)
- Approximate and extrapolated relative errors
- Fine grid convergence index ($GCI$)

## Prerequisites

### Linux
To build the application locally, you need:
- **CMake** (3.16 or higher)
- **C++ Compiler** (supporting C++17)
- **Qt 6 SDK** (including the `Widgets` component)

On Ubuntu/Debian, you can install the dependencies with:
```bash
sudo apt-get update
sudo apt-get install build-essential cmake qt6-base-dev qt6-base-private-dev
```

## Building Locally (Linux)

1. **Configure the project:**
   ```bash
   cmake -B build -DCMAKE_BUILD_TYPE=Release
   ```

2. **Build the application:**
   ```bash
   cmake --build build
   ```

3. **Run the application:**
   ```bash
   ./build/GciGui
   ```

## Downloading Executables (Linux & Windows)

You don't need to compile the application yourself. The project includes a GitHub Actions workflow that automatically builds it for you.

1. Push this project to a **GitHub repository**.
2. Navigate to the **Actions** tab in your repository.
3. Wait for the "Build and Release" workflow to complete.
4. Download the artifacts:
   - **Linux:** Download `GciGui-ubuntu-latest`. It contains a `.AppImage` file. To run it:
     ```bash
     chmod +x GciGui-x86_64.AppImage
     ./GciGui-x86_64.AppImage
     ```
   - **Windows:** Download `GciGui-windows-latest`. It contains a `.zip` file with the standalone `.exe` and all dependencies.

## Usage

1. **Input Grid Data:**
   - **Fine Grid:** Enter the representative cell size ($h_1$) and the parameter of interest ($\phi_1$).
   - **Medium Grid:** Enter $h_2$ and $\phi_2$.
   - **Coarse Grid:** Enter $h_3$ and $\phi_3$.
2. **Calculate:** Click the "Calculate" button.
3. **Results:** View the computed GCI and related parameters in the results pane.

## Releasing a New Version

To create a formal release with downloadable binaries:

1. Tag the current commit:
   ```bash
   git tag v1.0.0
   ```
2. Push the tag to GitHub:
   ```bash
   git push origin v1.0.0
   ```
GitHub Actions will automatically build the executables and create a new Release on your repository page.
Qt GUI conversion and modern build system setup by Gemini CLI.
