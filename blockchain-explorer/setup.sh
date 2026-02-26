#!/bin/bash

# AMMOcoin Explorer Setup Script
# This script helps set up the AMMOcoin blockchain explorer quickly

set -e

echo "🚀 AMMOcoin Blockchain Explorer Setup"
echo "====================================="
echo

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Helper functions
print_status() {
    echo -e "${BLUE}[INFO]${NC} $1"
}

print_success() {
    echo -e "${GREEN}[SUCCESS]${NC} $1"
}

print_warning() {
    echo -e "${YELLOW}[WARNING]${NC} $1"
}

print_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

# Check if command exists
command_exists() {
    command -v "$1" >/dev/null 2>&1
}

# Check prerequisites
check_prerequisites() {
    print_status "Checking prerequisites..."

    # Check Node.js
    if ! command_exists node; then
        print_error "Node.js is not installed. Please install Node.js 18+ from https://nodejs.org/"
        exit 1
    fi

    NODE_VERSION=$(node --version | cut -d'v' -f2 | cut -d'.' -f1)
    if [ "$NODE_VERSION" -lt 18 ]; then
        print_error "Node.js version 18+ is required. Current version: $(node --version)"
        exit 1
    fi

    print_success "Node.js $(node --version) found"

    # Check npm
    if ! command_exists npm; then
        print_error "npm is not installed"
        exit 1
    fi

    print_success "npm $(npm --version) found"

    # Check git
    if ! command_exists git; then
        print_error "Git is not installed"
        exit 1
    fi

    print_success "Git $(git --version | cut -d' ' -f3) found"
}

# Install dependencies
install_dependencies() {
    print_status "Installing dependencies..."
    npm install
    print_success "Dependencies installed successfully"
}

# Setup environment
setup_environment() {
    print_status "Setting up environment configuration..."

    if [ ! -f ".env.local" ]; then
        if [ -f ".env.example" ]; then
            cp .env.example .env.local
            print_success "Created .env.local from template"
        else
            print_warning ".env.example not found, creating basic .env.local"
            cat > .env.local << EOF
# AMMOcoin RPC Configuration
AMMOCOIN_RPC_URL=http://localhost:51473
AMMOCOIN_RPC_USER=explorer
AMMOCOIN_RPC_PASSWORD=change_this_password

# Explorer Configuration
NEXT_PUBLIC_EXPLORER_NAME="AMMOcoin Explorer"
NEXT_PUBLIC_NETWORK_NAME="AMMOcoin Mainnet"
NEXT_PUBLIC_COIN_SYMBOL="AMMO"

# Development Settings
NODE_ENV=development
EOF
        fi
    else
        print_warning ".env.local already exists, skipping creation"
    fi

    echo
    print_warning "IMPORTANT: Please edit .env.local with your AMMOcoin node configuration!"
    print_warning "You need to set:"
    print_warning "  - AMMOCOIN_RPC_URL (your node's RPC URL)"
    print_warning "  - AMMOCOIN_RPC_USER (RPC username)"
    print_warning "  - AMMOCOIN_RPC_PASSWORD (RPC password)"
    echo
}

# Check AMMOcoin node
check_ammocoin_node() {
    print_status "Checking AMMOcoin node connection..."

    # Source environment variables
    if [ -f ".env.local" ]; then
        export $(grep -v '^#' .env.local | xargs)
    fi

    RPC_URL=${AMMOCOIN_RPC_URL:-"http://localhost:51473"}
    RPC_USER=${AMMOCOIN_RPC_USER:-"explorer"}
    RPC_PASSWORD=${AMMOCOIN_RPC_PASSWORD:-""}

    if [ -z "$RPC_PASSWORD" ] || [ "$RPC_PASSWORD" = "change_this_password" ]; then
        print_warning "AMMOcoin RPC password not configured properly"
        print_warning "Please edit .env.local with your actual RPC credentials"
        return 1
    fi

    # Try to connect to the node
    print_status "Testing connection to $RPC_URL..."

    if command_exists curl; then
        RESPONSE=$(curl -s -u "$RPC_USER:$RPC_PASSWORD" \
            -d '{"jsonrpc":"1.0","id":"test","method":"getblockchaininfo","params":[]}' \
            -H 'content-type: text/plain;' \
            "$RPC_URL" 2>/dev/null || echo "FAILED")

        if echo "$RESPONSE" | grep -q '"result"'; then
            BLOCKS=$(echo "$RESPONSE" | grep -o '"blocks":[0-9]*' | cut -d':' -f2)
            print_success "Connected to AMMOcoin node! Current block height: $BLOCKS"
            return 0
        else
            print_warning "Could not connect to AMMOcoin node at $RPC_URL"
            print_warning "Please ensure:"
            print_warning "  1. AMMOcoin daemon is running"
            print_warning "  2. RPC is enabled in ammocoin.conf"
            print_warning "  3. RPC credentials are correct"
            return 1
        fi
    else
        print_warning "curl not found, skipping node connection test"
        return 1
    fi
}

# Run build
run_build() {
    print_status "Building the application..."
    npm run build
    print_success "Build completed successfully"
}

# Start development server
start_dev() {
    print_status "Starting development server..."
    print_success "Development server will start at http://localhost:3000"
    echo
    print_status "Press Ctrl+C to stop the server"
    echo
    npm run dev
}

# Main setup function
main() {
    echo "This script will help you set up the AMMOcoin Blockchain Explorer"
    echo

    # Check prerequisites
    check_prerequisites
    echo

    # Install dependencies
    install_dependencies
    echo

    # Setup environment
    setup_environment

    # Ask user if they want to test node connection
    echo
    read -p "Do you want to test the AMMOcoin node connection? (y/n): " -n 1 -r
    echo
    if [[ $REPLY =~ ^[Yy]$ ]]; then
        check_ammocoin_node
        echo
    fi

    # Ask user what they want to do next
    echo
    echo "Setup complete! What would you like to do next?"
    echo "1) Start development server (npm run dev)"
    echo "2) Build for production (npm run build)"
    echo "3) Exit and configure manually"
    echo
    read -p "Choose an option (1-3): " -n 1 -r
    echo

    case $REPLY in
        1)
            echo
            start_dev
            ;;
        2)
            echo
            run_build
            echo
            print_success "Production build completed!"
            print_status "You can now:"
            print_status "  - Start production server: npm start"
            print_status "  - Deploy the application to your hosting provider"
            print_status "  - See DEPLOYMENT_GUIDE.md for detailed deployment instructions"
            ;;
        3)
            echo
            print_success "Setup completed!"
            print_status "Next steps:"
            print_status "  1. Edit .env.local with your AMMOcoin node configuration"
            print_status "  2. Run 'npm run dev' to start development server"
            print_status "  3. See DEPLOYMENT_GUIDE.md for production deployment"
            ;;
        *)
            print_warning "Invalid option selected"
            ;;
    esac
}

# Run main function
main