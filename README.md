# Mu2e Tracking Quality Verification: XGBoost Framework
[![Code Base: Production Stable](https://img.shields.io/badge/Code%20Base-Production%20Stable-brightgreen)](#)
[![Physics Experiment: Mu2e Offline Pipeline](https://img.shields.io/badge/Physics%20Experiment-Mu2e%20Offline%20Pipeline-blue)](#)

This repository documents an exhaustive machine learning investigation focused on engineering an independent **XGBoost gradient-boosted decision tree (BDT)** classifier. This model serves as a high-precision, production-grade cross-verification framework running alongside the existing Artificial Neural Network (ANN) model currently deployed in the Mu2e experiment's offline track reconstruction pipeline.

The core objective of this framework is to classify track quality using precise measurements, isolate true signal conversion electrons ($CE$), and reject all the background signals.

> **Note on Project History:** This repository represents a full year of continuous local development, and physics feature engineering. It has been structured, modularized, and synchronized to GitHub as a complete, stable, and unified codebase.


##  1) Tech Stack & Workspace Environment
This workspace utilizes a high-performance machine learning stack managed through an isolated, length-locked Python virtual environment:
- **Gradient Boosting Engine:** `XGBoost Classifier` XGBoost is an optimized distributed gradient boosting library designed to be highly efficient, flexible and portable. It implements machine learning algorithms under the Gradient Boosting framework.
- **Deep Learning Frameworks:** `TensorFlow` & `PyTorch` (used for baseline comparative validation checks)
- **Interoperability & Deployment:** `ONNX` & `onnxruntime` (for cross-framework model porting)
- **Scientific Computing:** `NumPy`, `Pandas`, `Scikit-Learn`, `SciPy`, and `uproot` (for direct binary `.root` tree IO parsing)
- **Aesthetics & Chart Rendering:** `Matplotlib`, `Seaborn`, and `Graphviz`


##  2) Repository Architecture & Modular Walkthrough
The codebase has been split into 4 dedicated, independent research chapters to prevent memory leaks and variable collisions:

*   **`00_TrkQualTrain_main.ipynb`**: The master training pipeline. Handles raw feature loading from ROOT files, balances sample weights, tunes tree hyperparameters, trains the final 500-tree BDT ensemble, and save the model as .joblib for offline use.
*   **`01_data_perturbation.ipynb`**: The file that is responsible for creating and perturbing all of the required data sets.
*   **`02_factive_nactive_analysis.ipynb`**: Investigates the physical properties of track hits. Evaluates feature correlations and isolates the impact of `factive`  and `nactive` on the model's background rejection capabilities.
*   **`03_momerr_robustness_analysis.ipynb`**: A targeted stress-test notebook. Subjects the model to severe $\pm10\%$ and extreme $\pm50\%$ momentum error systematic variations to evaluate algorithmic stability under tracking resolution degradation.
*   **`04_all_data_perturbation_analysis.ipynb`**: The global analysis file. Compiles all perturbed data streams into a unified evaluation framework to compare static cut strategies against adaptive dynamic domain adaptation.


##  3) Physics Feature Matrix Map
The BDT classifier evaluates track quality based on seven core tracker and kinematic inputs defined inside `ML model/fmap.txt`:
1.  **`nactive`**: Number of active physical hits assigned to the track fit.
2.  **`factive`**: Fraction of total hits that remained active (`nactive / nhits`).
3.  **`t0err`**: Measured uncertainty [ns] in the track's initial production time ($t_0$).
4.  **`fambig`**: Fraction of hits with unresolved left-right drift ambiguities.
5.  **`fitcon`**: Joint fit $\chi^2$ consistency probability of the track trajectory.
6.  **`momerr`**: Calculated kinematic momentum error estimation [MeV/c].
7.  **`fstraws`**: Fraction of hits passing through material tracking straws.


##  4) Core Technical Importance: Domain Adaptation via Adaptive Cuts
The highlight of this investigation is the implementation of an **Adaptive Cut Strategy** to counter out-of-distribution tracker systematic errors. 

When tracking features are distorted by calibration shifts (such as shifting `momerr` by $\pm50\%$ or altering hit counts via `nactive +1`), keeping a rigid, static BDT threshold at `0.92` causes background leakage to vary wildly and signal track efficiency to drop significantly.

By parsing live ROC curves in memory, this framework calculates the precise dynamic threshold needed to absorb the distortion and **freeze background rejection at exactly 99.00%**. 

###  Strategic Comparison Matrix

| Configuration Dataset | Fixed BDT Cut | Signal Net Shift ($\Delta$) | Bkg Net Shift ($\Delta$) | Adaptive BDT Cut | Signal Net Shift ($\Delta$) | Final Bkg Count |
| :--- | :---: | :---: | :---: | :---: | :---: | :---: |
| **Original Baseline** | 0.92 | — | 0 | 0.9200 | — | 0 |
| **`nactive +1`** | 0.92 | +8,411 | +27 | 0.9334 | +7,347 | 19 |
| **`momerr +10%`** | 0.92 | -16,182 | -442 | 0.8989 | +9,381 | 37 |
| **`momerr -10%`** | 0.92 | +17,226 | +475 | 0.9365 | +8,811 | 35 |
| **`momerr +50%`** | 0.92 | -71,900 | -1,727 | 0.7915 | +13,511 | 51 |
| **`momerr -50%`** | 0.92 | +95,101 | +3,230 | 0.9812 | +16,507 | 49 |

###  Key Physics Insights 
*   **Signal Recovery:** Under an extreme `momerr +50%` tracking penalty, a static cut discards vital tracks due to model skepticism. Shifting the threshold adaptively to `0.7915` successfully recovers **+13,511 signal events** that would have been permanently lost.
*   **Background rejection:** Loosening the criteria for noisy files to rescue signal tracks does not flood the analysis with noise. Even under extreme distortions, final background track changes are held safely between **19 and 51 tracks**, proving the classifier's structural integrity.


##  5) Quick Start & Local Environment Setup
To clone this repository and recreate the exact package workspace, ensure you have your terminal active and execute the following steps:

### a. Clone the Repository
```bash
git clone https://github.com/<your-username>/Mu2e_XGboost_Project.git
cd Mu2e_XGboost_Project
```

### b. Establish Your Isolated Virtual Environment
```bash
python3 -m venv venv
source venv/bin/activate
```

### c. Install Synchronized Dependencies
```bash
pip install -r requirements.txt
```

*Note for macOS Users: If generating tree visualization models or running layout formatting components locally, ensure your laptop has OpenMP and Graphviz binary dependencies installed via Homebrew (`brew install libomp graphviz`).*

---

## Acknowledgments & Credits
- **Malik Farouh** — Researcher, Feature Engineering, Pipeline Architecture, and Lead ML Developer.
- **[Andrew Edmonds]** — Research Advisor, Theoretical Guidance, Programming Guidance, Mu2e Data Integration Strategies, and Core Scientific Contributor.
