# Opencv | Histogram Equalization and Image Filtering
### Part 1: Histogram Equalization

#### Requirements:
- Load an image.
- Compute and print histograms for R, G, and B channels.
- Equalize R, G, and B channels using `cv::equalizeHist()`.
- Convert the image to Lab color space and equalize only the luminance (L) channel.
- Display the original image, equalized image, and histograms.

#### Example Output:
![Histogram Equalization](link_to_histogram_equalization_image)

### Part 2: Image Filtering

#### Filters to Implement:
- **Median Blur:**
  - `cv::medianBlur()`
  - **Parameters:** kernel_size

- **Gaussian Blur:**
  - `cv::GaussianBlur()`
  - **Parameters:** kernel_size (square), σ (σx = σy)

- **Bilateral Filter:**
  - `cv::bilateralFilter()`
  - **Parameters:** kernel_size, σ_range (σr), σ_space (σs)

#### How to Run:
- Run the program and experiment with different filters and parameters.
- Optionally, use trackbars for interactive parameter adjustments.

#### Example Output:
![Filtered Image](link_to_filtered_image)

