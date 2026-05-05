[![master](https://img.shields.io/github/actions/workflow/status/nogai0702/GCI_GUI_Qt/build.yml?branch=master&label=master)](https://github.com/nogai0702/GCI_GUI_Qt/actions/workflows/build.yml)
[![testing](https://img.shields.io/github/actions/workflow/status/nogai0702/GCI_GUI_Qt/build.yml?branch=testing&label=testing)](https://github.com/nogai0702/GCI_GUI_Qt/actions/workflows/build.yml)

# GCI Calculator GUI

![GCI Calculator Screenshot](docs/screenshot.png) 

A cross-platform Qt-based graphical user interface for calculating the **Grid Convergence Index (GCI)**, based on the procedure presented by Celik et al. (2008). 

This application calculates:
- Grid refinement ratios ($r_{21}, r_{32}$)
- Apparent order of the method ($p$)
- Extrapolated values ($\phi_{ext}$)
- Approximate and extrapolated relative errors
- Fine grid convergence index ($GCI^{21}$)

## Download & Installation

You do not need to compile the application yourself. Pre-compiled binaries for Linux, Windows, and macOS are automatically generated for every release.

1. Go to the [Releases](../../releases/latest) page of this repository.
2. Download the appropriate file for your operating system:

   - **Windows:** Download the `.exe` file. It is a standalone portable executable.
   
   - **Linux:** Download the `.AppImage` file. 
     ```bash
     chmod +x GciGui-x86_64.AppImage
     ./GciGui-x86_64.AppImage
     ```

   - **macOS (Intel & Apple Silicon):** Download the macOS `.zip` file and extract `GciGui.app`. 
     > **Note on macOS Security:** Because this is an open-source tool and not signed with a paid Apple Developer certificate, macOS Gatekeeper will flag it as an "unidentified developer." 
     > To run it: Right-click the app and select **Open**, or run the following command in your terminal to clear the quarantine flag:
     > 
```bash
     > xattr -cr /path/to/GciGui.app
     > ```

## Usage

1. **Input Grid Data:**
   - **Fine Grid:** Enter the representative cell size ($h_1$) and the parameter of interest ($\phi_1$).
   - **Medium Grid:** Enter $h_2$ and $\phi_2$.
   - **Coarse Grid:** Enter $h_3$ and $\phi_3$.
2. **Calculate:** Click the "Run GCI Analysis" button.
3. **Results:** View the computed GCI, Apparent Order, and related parameters in the results pane. Detailed calculation warnings will appear in the log window.

---

## Building Locally (For Developers)

If you wish to compile the application from source, you will need **CMake** (3.16+), a **C++17 Compiler**, and the **Qt 6 SDK**.

### Linux
```bash
sudo apt-get update && sudo apt-get install build-essential cmake qt6-base-dev
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
./build/GciGui
```

### macOS (via Homebrew)
```bash
brew install cmake qt@6
cmake -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH=$(brew --prefix qt@6)
cmake --build build
macdeployqt build/GciGui.app
```

## Releasing a New Version

The CI/CD pipeline uses GitHub Actions to automatically build and package the `.exe`, `.AppImage`, and `.app` bundle whenever a new tag is pushed.

```bash
git tag v1.0.0
git push origin v1.0.0
```

## License

This project is licensed under the **GNU General Public License v3.0 (GPLv3)** - see the `LICENSE` file for details.