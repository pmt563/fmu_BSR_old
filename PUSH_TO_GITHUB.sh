#!/bin/bash
cd /home/minhtuan958/Documents/emtek/sdv/zonal_BSR_huynguyen/BabySafetyReminder/HIL_Realization/Phase3/Implementation/vehicle_computer/vECU_Layer

# Initialize git if needed
git init

# Add all files
git add .

# Commit
git commit -m "Add Windows container with automated CI/CD

- Windows Dockerfile using Server Core + Python 3.11
- GitHub Actions workflow for automated builds
- KUKSA address configurable via command-line
- Documentation and usage instructions"

# Push to GitHub
git push -u origin main --force

echo "✅ Pushed to GitHub!"
echo "Check workflow at: https://github.com/pmt563/fmu_BSR_old/actions"
