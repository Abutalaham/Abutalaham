/**
 * FoodHub - Main Application Module
 * Production-Ready Frontend Architecture
 * Handles: Cart Management, Form Validation, Search, API Integration
 */

// ========================================
// CONFIGURATION & CONSTANTS
// ========================================
const CONFIG = {
  API_BASE_URL: 'https://api.example.com/api',
  CART_STORAGE_KEY: 'foodhub_cart',
  USER_STORAGE_KEY: 'foodhub_user',
  ANALYTICS_ID: 'UA-XXXXXXXXX-X', // Replace with actual GA ID
  TAX_RATE: 0.10,
  DELIVERY_FEE: 2.99,
};

// Store application state
const appState = {
  cart: [],
  user: null,
  searchQuery: '',
  selectedCategories: [],
  sortBy: 'name',
};

// ========================================
// UTILITY FUNCTIONS
// ========================================

/**
 * Initialize tooltips and UI enhancements
 */
function initializeApp() {
  loadCart();
  loadUser();
  attachEventListeners();
  setupLazyLoading();
  initializeAnalytics();
  updateCartBadge();
}

/**
 * Show notification toast
 */
function showNotification(message, type = 'info', duration = 3000) {
  const toast = document.createElement('div');
  toast.className = `notification notification-${type} slide-in-up`;
  toast.innerHTML = `
    <div class="notification-content">
      <span class="notification-message">${escapeHtml(message)}</span>
      <button class="notification-close" onclick="this.parentElement.parentElement.remove()">×</button>
    </div>
  `;
  
  document.body.appendChild(toast);
  
  setTimeout(() => {
    toast.classList.add('fade-out');
    setTimeout(() => toast.remove(), 300);
  }, duration);
}

/**
 * Escape HTML to prevent XSS
 */
function escapeHtml(text) {
  const div = document.createElement('div');
  div.textContent = text;
  return div.innerHTML;
}

/**
 * Show loading state
 */
function showLoading(elementSelector) {
  const element = document.querySelector(elementSelector);
  if (element) {
    element.innerHTML = `
      <div class="skeleton-loading">
        <div class="skeleton-item"></div>
        <div class="skeleton-item"></div>
        <div class="skeleton-item"></div>
      </div>
    `;
    element.classList.add('loading');
  }
}

/**
 * Hide loading state
 */
function hideLoading(elementSelector) {
  const element = document.querySelector(elementSelector);
  if (element) {
    element.classList.remove('loading');
  }
}

/**
 * Format currency
 */
function formatCurrency(amount) {
  return new Intl.NumberFormat('en-US', {
    style: 'currency',
    currency: 'USD',
    minimumFractionDigits: 2,
    maximumFractionDigits: 2,
  }).format(amount);
}

// ========================================
// FORM VALIDATION MODULE
// ========================================

const FormValidator = {
  /**
   * Validation rules
   */
  rules: {
    email: {
      pattern: /^[^\s@]+@[^\s@]+\.[^\s@]+$/,
      message: 'Please enter a valid email address',
    },
    phone: {
      pattern: /^[\+]?[(]?[0-9]{1,4}[)]?[-\s\.]?[(]?[0-9]{1,4}[)]?[-\s\.]?[0-9]{1,9}$/,
      message: 'Please enter a valid phone number',
    },
    name: {
      pattern: /^[a-zA-Z\s]{2,50}$/,
      message: 'Name must be 2-50 characters and contain only letters',
    },
    address: {
      minLength: 10,
      message: 'Address must be at least 10 characters',
    },
    password: {
      minLength: 6,
      message: 'Password must be at least 6 characters',
    },
  },

  /**
   * Validate single field
   */
  validateField(fieldName, value) {
    const rule = this.rules[fieldName];
    if (!rule) return { valid: true };

    // Check pattern
    if (rule.pattern && !rule.pattern.test(value)) {
      return { valid: false, message: rule.message };
    }

    // Check minimum length
    if (rule.minLength && value.length < rule.minLength) {
      return { valid: false, message: rule.message };
    }

    // Check required
    if (!value || value.trim() === '') {
      return { valid: false, message: `${fieldName} is required` };
    }

    return { valid: true };
  },

  /**
   * Validate form
   */
  validateForm(formElement) {
    const inputs = formElement.querySelectorAll('input, textarea, select');
    let isValid = true;

    inputs.forEach((input) => {
      const validation = this.validateField(input.name, input.value);
      
      if (!validation.valid) {
        this.showFieldError(input, validation.message);
        isValid = false;
      } else {
        this.clearFieldError(input);
      }
    });

    return isValid;
  },

  /**
   * Show field error
   */
  showFieldError(input, message) {
    input.classList.add('input-error');
    const errorDiv = document.createElement('div');
    errorDiv.className = 'field-error';
    errorDiv.textContent = message;

    // Remove existing error
    const existingError = input.parentElement.querySelector('.field-error');
    if (existingError) existingError.remove();

    input.parentElement.appendChild(errorDiv);
  },

  /**
   * Clear field error
   */
  clearFieldError(input) {
    input.classList.remove('input-error');
    const errorDiv = input.parentElement.querySelector('.field-error');
    if (errorDiv) errorDiv.remove();
  },
};

// ========================================
// CART MANAGEMENT MODULE
// ========================================

const CartManager = {
  /**
   * Add item to cart
   */
  addToCart(item) {
    const existingItem = appState.cart.find((cartItem) => cartItem.id === item.id);

    if (existingItem) {
      existingItem.quantity += item.quantity || 1;
      existingItem.subtotal = existingItem.price * existingItem.quantity;
    } else {
      appState.cart.push({
        ...item,
        quantity: item.quantity || 1,
        subtotal: item.price * (item.quantity || 1),
      });
    }

    this.saveCart();
    updateCartBadge();
    showNotification(`${item.name} added to cart!`, 'success');
  },

  /**
   * Remove item from cart
   */
  removeFromCart(itemId) {
    appState.cart = appState.cart.filter((item) => item.id !== itemId);
    this.saveCart();
    updateCartBadge();
    showNotification('Item removed from cart', 'info');
  },

  /**
   * Update item quantity
   */
  updateQuantity(itemId, quantity) {
    const item = appState.cart.find((i) => i.id === itemId);
    if (item) {
      if (quantity <= 0) {
        this.removeFromCart(itemId);
      } else {
        item.quantity = quantity;
        item.subtotal = item.price * quantity;
        this.saveCart();
        updateCartBadge();
      }
    }
  },

  /**
   * Clear cart
   */
  clearCart() {
    appState.cart = [];
    this.saveCart();
    updateCartBadge();
  },

  /**
   * Save cart to localStorage
   */
  saveCart() {
    localStorage.setItem(CONFIG.CART_STORAGE_KEY, JSON.stringify(appState.cart));
  },

  /**
   * Get cart total
   */
  getCartTotal() {
    return appState.cart.reduce((total, item) => total + item.subtotal, 0);
  },

  /**
   * Get cart item count
   */
  getCartCount() {
    return appState.cart.reduce((count, item) => count + item.quantity, 0);
  },
};

// ========================================
// SEARCH & FILTER MODULE
// ========================================

const SearchFilter = {
  /**
   * Search items by name and description
   */
  searchItems(items, query) {
    if (!query.trim()) return items;

    const lowerQuery = query.toLowerCase();
    return items.filter(
      (item) =>
        item.name.toLowerCase().includes(lowerQuery) ||
        (item.description && item.description.toLowerCase().includes(lowerQuery))
    );
  },

  /**
   * Filter by category
   */
  filterByCategory(items, categories) {
    if (!categories || categories.length === 0) return items;
    return items.filter((item) => categories.includes(item.category));
  },

  /**
   * Filter by price range
   */
  filterByPrice(items, minPrice, maxPrice) {
    return items.filter((item) => item.price >= minPrice && item.price <= maxPrice);
  },

  /**
   * Sort items
   */
  sortItems(items, sortBy) {
    const sorted = [...items];

    switch (sortBy) {
      case 'price-low':
        return sorted.sort((a, b) => a.price - b.price);
      case 'price-high':
        return sorted.sort((a, b) => b.price - a.price);
      case 'rating':
        return sorted.sort((a, b) => (b.rating || 0) - (a.rating || 0));
      case 'name':
        return sorted.sort((a, b) => a.name.localeCompare(b.name));
      default:
        return sorted;
    }
  },

  /**
   * Apply all filters and search
   */
  applyFilters(items, searchQuery, categories, sortBy, priceRange) {
    let filtered = items;

    // Apply search
    filtered = this.searchItems(filtered, searchQuery);

    // Apply category filter
    filtered = this.filterByCategory(filtered, categories);

    // Apply price filter
    if (priceRange && priceRange.min !== undefined && priceRange.max !== undefined) {
      filtered = this.filterByPrice(filtered, priceRange.min, priceRange.max);
    }

    // Apply sort
    filtered = this.sortItems(filtered, sortBy);

    return filtered;
  },
};

// ========================================
// API INTEGRATION MODULE
// ========================================

const APIClient = {
  /**
   * Make HTTP request
   */
  async request(endpoint, options = {}) {
    const defaultOptions = {
      method: 'GET',
      headers: {
        'Content-Type': 'application/json',
      },
    };

    const config = { ...defaultOptions, ...options };
    const url = `${CONFIG.API_BASE_URL}${endpoint}`;

    try {
      const response = await fetch(url, config);

      if (!response.ok) {
        throw new Error(`API Error: ${response.status} ${response.statusText}`);
      }

      return await response.json();
    } catch (error) {
      console.error('API Request Error:', error);
      throw error;
    }
  },

  /**
   * Submit order
   */
  async submitOrder(orderData) {
    return this.request('/orders', {
      method: 'POST',
      body: JSON.stringify(orderData),
    });
  },

  /**
   * Get foods
   */
  async getFoods(filters = {}) {
    const params = new URLSearchParams(filters);
    return this.request(`/foods?${params.toString()}`);
  },

  /**
   * Get categories
   */
  async getCategories() {
    return this.request('/categories');
  },
};

// ========================================
// IMAGE OPTIMIZATION
// ========================================

function setupLazyLoading() {
  // Modern browser Intersection Observer
  if ('IntersectionObserver' in window) {
    const imageObserver = new IntersectionObserver((entries, observer) => {
      entries.forEach((entry) => {
        if (entry.isIntersecting) {
          const img = entry.target;
          if (img.dataset.src) {
            img.src = img.dataset.src;
            img.removeAttribute('data-src');
          }
          if (img.dataset.srcset) {
            img.srcset = img.dataset.srcset;
            img.removeAttribute('data-srcset');
          }
          observer.unobserve(img);
        }
      });
    });

    document.querySelectorAll('img[data-src]').forEach((img) => imageObserver.observe(img));
  } else {
    // Fallback for older browsers
    document.querySelectorAll('img[data-src]').forEach((img) => {
      img.src = img.dataset.src;
    });
  }
}

// ========================================
// USER & CART PERSISTENCE
// ========================================

function loadCart() {
  const saved = localStorage.getItem(CONFIG.CART_STORAGE_KEY);
  if (saved) {
    try {
      appState.cart = JSON.parse(saved);
    } catch (e) {
      console.error('Error loading cart:', e);
    }
  }
}

function loadUser() {
  const saved = localStorage.getItem(CONFIG.USER_STORAGE_KEY);
  if (saved) {
    try {
      appState.user = JSON.parse(saved);
    } catch (e) {
      console.error('Error loading user:', e);
    }
  }
}

function saveUser(userData) {
  appState.user = userData;
  localStorage.setItem(CONFIG.USER_STORAGE_KEY, JSON.stringify(userData));
}

// ========================================
// UI UPDATE FUNCTIONS
// ========================================

function updateCartBadge() {
  const badges = document.querySelectorAll('.cart-badge');
  const count = CartManager.getCartCount();
  
  badges.forEach((badge) => {
    if (count > 0) {
      badge.textContent = count;
      badge.style.display = 'flex';
    } else {
      badge.style.display = 'none';
    }
  });
}

function updateCartSummary() {
  const subtotal = CartManager.getCartTotal();
  const tax = subtotal * CONFIG.TAX_RATE;
  const total = subtotal + tax + CONFIG.DELIVERY_FEE;

  const elements = {
    subtotal: document.querySelector('[data-price="subtotal"]'),
    tax: document.querySelector('[data-price="tax"]'),
    delivery: document.querySelector('[data-price="delivery"]'),
    total: document.querySelector('[data-price="total"]'),
  };

  if (elements.subtotal) elements.subtotal.textContent = formatCurrency(subtotal);
  if (elements.tax) elements.tax.textContent = formatCurrency(tax);
  if (elements.delivery) elements.delivery.textContent = formatCurrency(CONFIG.DELIVERY_FEE);
  if (elements.total) elements.total.textContent = formatCurrency(total);

  return { subtotal, tax, delivery: CONFIG.DELIVERY_FEE, total };
}

// ========================================
// EVENT LISTENERS & INTERACTIONS
// ========================================

function attachEventListeners() {
  // Order form submission
  const orderForm = document.querySelector('.order');
  if (orderForm) {
    orderForm.addEventListener('submit', handleOrderSubmit);
  }

  // Search functionality
  const searchInputs = document.querySelectorAll('input[type="search"]');
  searchInputs.forEach((input) => {
    input.addEventListener('input', (e) => {
      appState.searchQuery = e.target.value;
      // Trigger search on the page if needed
      const searchEvent = new CustomEvent('searchUpdated', {
        detail: { query: appState.searchQuery },
      });
      document.dispatchEvent(searchEvent);
    });
  });

  // Quantity input validation
  document.addEventListener('change', (e) => {
    if (e.target.name === 'quantity') {
      const quantity = parseInt(e.target.value) || 0;
      if (quantity < 1) e.target.value = 1;
      if (quantity > 99) e.target.value = 99;
    }
  });
}

/**
 * Handle order form submission
 */
async function handleOrderSubmit(e) {
  e.preventDefault();

  // Validate form
  if (!FormValidator.validateForm(e.target)) {
    showNotification('Please fix the errors before submitting', 'error');
    return;
  }

  // Check cart
  if (appState.cart.length === 0) {
    showNotification('Your cart is empty. Add items before ordering', 'warning');
    return;
  }

  const button = e.target.querySelector('button[type="submit"]');
  const originalText = button.textContent;

  try {
    // Show loading state
    button.disabled = true;
    button.textContent = 'Processing...';
    showLoading('.order');

    // Collect form data
    const formData = new FormData(e.target);
    const orderData = {
      customer: {
        name: formData.get('full-name'),
        email: formData.get('email'),
        phone: formData.get('contact'),
        address: formData.get('address'),
        notes: formData.get('notes'),
      },
      items: appState.cart,
      paymentMethod: formData.get('payment'),
      pricing: updateCartSummary(),
      timestamp: new Date().toISOString(),
    };

    // Simulate API call
    console.log('Submitting order:', orderData);
    const response = await simulateAPICall(orderData);

    if (response.success) {
      // Save user info
      saveUser(orderData.customer);

      // Clear cart
      CartManager.clearCart();

      // Show success
      showNotification('Order placed successfully! Order ID: ' + response.orderId, 'success', 5000);

      // Clear form
      e.target.reset();

      // Redirect after delay
      setTimeout(() => {
        window.location.href = `order-confirmation.html?orderId=${response.orderId}`;
      }, 2000);
    } else {
      throw new Error(response.message || 'Failed to place order');
    }
  } catch (error) {
    console.error('Order submission error:', error);
    showNotification('Error: ' + error.message, 'error');
  } finally {
    // Reset button state
    button.disabled = false;
    button.textContent = originalText;
    hideLoading('.order');
  }
}

/**
 * Simulate API call (replace with real API)
 */
function simulateAPICall(data) {
  return new Promise((resolve) => {
    setTimeout(() => {
      resolve({
        success: true,
        orderId: 'ORD-' + Date.now(),
        message: 'Order placed successfully',
      });
    }, 1500);
  });
}

// ========================================
// ANALYTICS
// ========================================

function initializeAnalytics() {
  // Google Analytics
  if (CONFIG.ANALYTICS_ID && CONFIG.ANALYTICS_ID !== 'UA-XXXXXXXXX-X') {
    window.dataLayer = window.dataLayer || [];
    function gtag() {
      dataLayer.push(arguments);
    }
    gtag('js', new Date());
    gtag('config', CONFIG.ANALYTICS_ID);
  }

  // Track page views
  if (window.gtag) {
    window.gtag('pageview');
  }
}

/**
 * Track custom event
 */
function trackEvent(eventName, eventData = {}) {
  if (window.gtag) {
    window.gtag('event', eventName, eventData);
  }
  console.log('Event tracked:', eventName, eventData);
}

// ========================================
// INITIALIZATION
// ========================================

// Initialize app when DOM is ready
if (document.readyState === 'loading') {
  document.addEventListener('DOMContentLoaded', initializeApp);
} else {
  initializeApp();
}
