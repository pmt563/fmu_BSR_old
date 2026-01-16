# Git Push Commands for Windows Container

## Quick Push to GitHub

```bash
cd /home/minhtuan958/Documents/emtek/sdv/zonal_BSR_huynguyen/BabySafetyReminder/HIL_Realization/Phase3/Implementation/vehicle_computer/vECU_Layer

# Initialize git (if not already done)
git init

# Add remote (if not already done)
git remote add origin https://github.com/pmt563/fmu_BSR_old.git 2>/dev/null || true

# Add all files
git add .

# Commit
git commit -m "Add Windows container with automated CI/CD

- Add Dockerfile.windows for Windows Server Core
- Add GitHub Actions workflow for automated builds
- Configure KUKSA address as command-line parameter
- Add comprehensive documentation"

# Push to GitHub
git push -u origin main
```

## What Happens Next

1. **GitHub Actions triggers** (~15-20 minutes)
   - Workflow: `.github/workflows/build-windows.yml`
   - Runs on: `windows-latest` runner
   - Builds Windows container image

2. **Image pushed to GHCR**
   - Registry: `ghcr.io/pmt563/fmu_bsr_old`
   - Tags: `windows-latest`, `windows-main`, `windows-<sha>`

3. **Anyone can pull and run**
   ```powershell
   docker pull ghcr.io/pmt563/fmu_bsr_old:windows-latest
   docker run ghcr.io/pmt563/fmu_bsr_old:windows-latest
   ```

## Verify Workflow

After pushing, check:
- https://github.com/pmt563/fmu_BSR_old/actions
- Look for "Build Windows Container" workflow
- Wait for green checkmark ✅

## Files Being Pushed

```
vECU_Layer/
├── .github/workflows/
│   └── build-windows.yml       ✅ Auto-build workflow
├── .dockerignore               ✅ Exclude unnecessary files
├── .gitignore                  ✅ Git exclusions
├── Dockerfile.windows          ✅ Windows container
├── GIT_PUSH_INSTRUCTIONS.md    📝 This file
├── README.md                   📝 Main documentation
├── README_WINDOWS_CONTAINER.md 📝 Detailed guide
├── requirements.txt            📦 Python dependencies
├── fmus/                       📦 FMU files (with Windows DLLs)
│   ├── vECU_Airbag.fmu
│   ├── vecu_zonal.fmu
│   └── cockpit_test.fmu
└── src/                        💻 Application code
    ├── host_cosim_and_connect_kuksa.py
    └── cosim_environment.py
```
