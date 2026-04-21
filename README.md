# GCI Calculator GUI

[![Build and Release](https://github.com/nogai0702/GCI_GUI_Qt/actions/workflows/build.yml/badge.svg)](https://github.com/nogai0702/GCI_GUI_Qt/actions/workflows/build.yml)

A modern, cross-platform Qt 6 application for calculating the **Grid Convergence Index (GCI)**. This tool implements the widely-recognized procedure presented by Celik et al. (2008) to estimate numerical uncertainty in computational simulations.

## Key Features

- **Modern UI:** Built with Qt 6, featuring a clean dashboard and detailed reporting.
- **Theme Support:** Automatically detects system theme (Dark/Light mode) with manual overrides in the View menu.
- **Real-time Validation:** Input fields are validated for numerical correctness.
- **Detailed Reports:** Generates a comprehensive summary including:
  - Grid refinement ratios ($r_{21}, r_{32}$)
  - Apparent order of convergence ($p$)
  - Extrapolated values ($\phi_{ext}$)
  - Approximate and extrapolated relative errors ($e_a, e_{ext}$)
  - Fine grid convergence index ($GCI$)
- **Cross-Platform:** Native performance on Linux, Windows, and macOS.

## Architecture

The project is structured into clean layers:
- `src/core`: Pure C++17 logic for GCI calculations.
- `src/gui`: Qt-based user interface using `.ui` forms and custom `.qss` styling.
- `GCI.c`: Original CLI implementation preserved for reference.

## Getting Started

### Prerequisites

- **CMake** (3.16+)
- **C++17 Compiler**
- **Qt 6 SDK** (Widgets module)

#### Linux (Ubuntu/Debian)
```bash
sudo apt-get update
sudo apt-get install build-essential cmake qt6-base-dev
```

### Building from Source

1. **Configure:**
   ```bash
   cmake -B build -DCMAKE_BUILD_TYPE=Release
   ```
2. **Build:**
   ```bash
   cmake --build build
   ```
3. **Run:**
   ```bash
   ./build/GciGui
   ```

## Downloads (Pre-built Binaries)

The project uses GitHub Actions to automatically build portable executables for every update.

1. Go to the **[Releases](https://github.com/nogai/GCI_QT_gui/releases)** page.
2. Download the appropriate package:
   - **Linux:** `.AppImage` (portable, works on most distributions).
   - **Windows:** `.zip` containing the standalone executable.

## Usage

1. **Input Data:**
   - Enter representative cell sizes ($h$) and your parameter of interest ($\phi$) for three grids: Fine ($h_1$), Medium ($h_2$), and Coarse ($h_3$).
2. **Analyze:** Click **Calculate** to process the data.
3. **Review:** Results appear in the dashboard metrics. Check the "Detailed Report" log for full mathematical breakdowns and any convergence warnings.

## References

- Celik, I. B., Ghia, U., Roache, P. J., & Freitas, C. J. (2008). *Procedure for Estimation and Reporting of Uncertainty Due to Discretization in CFD Applications*. Journal of Fluids Engineering.

---
*Developed and modernized by Gemini CLI.*
