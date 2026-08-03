# Perturbation Analysis Study

This directory contains a suite of notebooks for evaluating an XGBoost model for the Mu2e tracking quality verification pipeline, specifically analyzing stability under data distortions.

## File Walkthrough

* **00_TrkQualTrain_main.ipynb:** Handles feature loading, model training, and saves the final BDT model.
* **01_data_perturbation.ipynb:** Generates and perturbs the required datasets.
* **02_factive_nactive_analysis.ipynb:** Analyzes physical track hit properties and background rejection.
* **03_momerr_robustness_analysis.ipynb:** Evaluates model robustness against ±10% and ±50% momentum errors.
* **04_all_data_perturbation_analysis.ipynb:** Consolidates all analyses to compare static and dynamic evaluation strategies.
