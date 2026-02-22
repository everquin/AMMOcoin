# AMMOcoin Blockchain Explorer - Deployment Guide

Complete instructions for setting up, configuring, and deploying the AMMOcoin blockchain explorer.

## 📋 Table of Contents

- [Prerequisites](#prerequisites)
- [Quick Start](#quick-start)
- [AMMOcoin Node Setup](#ammocoin-node-setup)
- [Explorer Configuration](#explorer-configuration)
- [Development Setup](#development-setup)
- [Production Deployment](#production-deployment)
- [Troubleshooting](#troubleshooting)
- [Advanced Configuration](#advanced-configuration)

---

## 🔧 Prerequisites

### System Requirements

- **Node.js 18+** - [Download from nodejs.org](https://nodejs.org/)
- **npm 9+** or **yarn 3+** - Package manager
- **Git** - Version control
- **AMMOcoin Node** - Running `ammocoind` daemon

### Hardware Recommendations

**Development:**
- 4GB RAM minimum
- 2GB free disk space
- Stable internet connection

**Production:**
- 8GB RAM recommended
- 10GB+ free disk space (depending on data caching)
- High-bandwidth internet connection
- SSL certificate for HTTPS

---

## ⚡ Quick Start

### 1. Clone and Install

```bash
# Clone the repository
git clone https://github.com/ammocoin/ammocoin-explorer.git
cd ammocoin-explorer

# Install dependencies
npm install

# Copy environment template
cp .env.example .env.local
```

### 2. Configure Environment

Edit `.env.local` with your AMMOcoin node details:

```bash
# AMMOcoin RPC Configuration
NEXT_PUBLIC_AMMOCOIN_RPC_URL=http://localhost:51473
NEXT_PUBLIC_AMMOCOIN_RPC_USER=explorer
NEXT_PUBLIC_AMMOCOIN_RPC_PASSWORD=your_secure_password

# Explorer Configuration
NEXT_PUBLIC_EXPLORER_NAME="AMMOcoin Explorer"
NEXT_PUBLIC_NETWORK_NAME="AMMOcoin Mainnet"
NEXT_PUBLIC_COIN_SYMBOL="AMMO"
```

### 3. Start Development Server

```bash
npm run dev
```

Open [http://localhost:3000](http://localhost:3000) in your browser.

---

## 🏗️ AMMOcoin Node Setup

### Required Configuration

Your AMMOcoin node must be configured to accept RPC connections. Add these settings to your `ammocoin.conf` file:

```ini
# RPC Server Configuration
server=1
rpcuser=explorer
rpcpassword=your_secure_password_here
rpcallowip=127.0.0.1
rpcallowip=10.0.0.0/8
rpcallowip=172.16.0.0/12
rpcallowip=192.168.0.0/16
rpcport=51473

# Optional: Increase RPC timeout for large requests
rpctimeout=300

# Optional: Enable transaction indexing for better performance
txindex=1

# Optional: Enable address indexing (if available)
addressindex=1
timestampindex=1
spentindex=1
```

### Starting Your Node

```bash
# Start the daemon
./ammocoind -daemon

# Check if it's running
./ammocoin-cli getblockchaininfo

# Stop the daemon (when needed)
./ammocoin-cli stop
```

### Security Notes

⚠️ **Important Security Considerations:**

1. **Never expose RPC to the internet** - Use firewalls and VPNs
2. **Use strong passwords** - Generate cryptographically secure passwords
3. **Limit RPC access** - Only allow necessary IP addresses
4. **Monitor access logs** - Watch for unauthorized access attempts

---

## ⚙️ Explorer Configuration

### Environment Variables

Create `.env.local` with all necessary configuration:

```bash
# === REQUIRED SETTINGS ===

# AMMOcoin Node RPC
NEXT_PUBLIC_AMMOCOIN_RPC_URL=http://localhost:51473
NEXT_PUBLIC_AMMOCOIN_RPC_USER=explorer
NEXT_PUBLIC_AMMOCOIN_RPC_PASSWORD=secure_password_here

# === OPTIONAL SETTINGS ===

# Explorer Branding
NEXT_PUBLIC_EXPLORER_NAME="AMMOcoin Explorer"
NEXT_PUBLIC_NETWORK_NAME="AMMOcoin Mainnet"
NEXT_PUBLIC_COIN_SYMBOL="AMMO"
NEXT_PUBLIC_SITE_URL=https://explorer.ammocoin.org
NEXT_PUBLIC_SITE_DESCRIPTION="AMMOcoin Blockchain Explorer"

# External APIs (optional)
NEXT_PUBLIC_COINMARKETCAP_API_KEY=your_cmc_api_key

# Analytics (optional)
NEXT_PUBLIC_GOOGLE_ANALYTICS_ID=G-XXXXXXXXXX

# Development Settings
NODE_ENV=production
```

### Network Configuration

For different networks (testnet, regtest), adjust your settings:

**Testnet:**
```bash
NEXT_PUBLIC_AMMOCOIN_RPC_URL=http://localhost:51475
NEXT_PUBLIC_NETWORK_NAME="AMMOcoin Testnet"
NEXT_PUBLIC_EXPLORER_NAME="AMMOcoin Testnet Explorer"
```

**Regtest:**
```bash
NEXT_PUBLIC_AMMOCOIN_RPC_URL=http://localhost:51477
NEXT_PUBLIC_NETWORK_NAME="AMMOcoin Regtest"
NEXT_PUBLIC_EXPLORER_NAME="AMMOcoin Regtest Explorer"
```

---

## 🔨 Development Setup

### Local Development

```bash
# Install dependencies
npm install

# Start development server
npm run dev

# Run in different modes
npm run dev -- --port 3001        # Custom port
npm run dev -- --hostname 0.0.0.0 # Allow external connections
```

### Development Scripts

```bash
# Development
npm run dev          # Start development server
npm run build        # Build for production
npm run start        # Start production server
npm run lint         # Run ESLint
npm run type-check   # TypeScript type checking
```

### Code Quality

```bash
# Install development tools
npm install --save-dev prettier eslint @typescript-eslint/parser

# Format code
npx prettier --write "src/**/*.{ts,tsx,js,jsx}"

# Lint code
npm run lint

# Type check
npm run type-check
```

---

## 🚀 Production Deployment

### Option 1: Vercel (Recommended)

**Automatic Deployment:**
1. Push code to GitHub
2. Connect repository to [Vercel](https://vercel.com)
3. Configure environment variables in Vercel dashboard
4. Deploy automatically on each push

**Manual Deployment:**
```bash
# Install Vercel CLI
npm i -g vercel

# Deploy
vercel

# Configure environment variables
vercel env add NEXT_PUBLIC_AMMOCOIN_RPC_URL
vercel env add NEXT_PUBLIC_AMMOCOIN_RPC_USER
vercel env add NEXT_PUBLIC_AMMOCOIN_RPC_PASSWORD

# Deploy production
vercel --prod
```

### Option 2: Static Export

For hosting on any static file server:

```bash
# Enable static export in next.config.js
# Uncomment these lines:
# output: 'export',
# trailingSlash: true,
# distDir: 'out',

# Build static version
npm run build

# Deploy the 'out' directory to your static host
# (Netlify, Cloudflare Pages, AWS S3, etc.)
```

### Option 3: Docker

**Create Dockerfile:**
```dockerfile
FROM node:18-alpine

WORKDIR /app

# Copy package files
COPY package*.json ./
RUN npm ci --only=production

# Copy source code
COPY . .

# Build application
RUN npm run build

# Expose port
EXPOSE 3000

# Start application
CMD ["npm", "start"]
```

**Build and run:**
```bash
# Build image
docker build -t ammocoin-explorer .

# Run container
docker run -p 3000:3000 \
  -e NEXT_PUBLIC_AMMOCOIN_RPC_URL=http://your-node:51473 \
  -e NEXT_PUBLIC_AMMOCOIN_RPC_USER=explorer \
  -e NEXT_PUBLIC_AMMOCOIN_RPC_PASSWORD=password \
  ammocoin-explorer
```

### Option 4: Traditional VPS

**Ubuntu/Debian Setup:**
```bash
# Update system
sudo apt update && sudo apt upgrade -y

# Install Node.js
curl -fsSL https://deb.nodesource.com/setup_18.x | sudo -E bash -
sudo apt-get install -y nodejs

# Clone and setup
git clone https://github.com/ammocoin/ammocoin-explorer.git
cd ammocoin-explorer
npm install
cp .env.example .env.local

# Edit configuration
nano .env.local

# Build for production
npm run build

# Install PM2 for process management
sudo npm install -g pm2

# Start with PM2
pm2 start npm --name "ammocoin-explorer" -- start
pm2 save
pm2 startup
```

### SSL Certificate Setup

**Using Nginx + Let's Encrypt:**
```bash
# Install Nginx
sudo apt install nginx

# Install Certbot
sudo apt install certbot python3-certbot-nginx

# Create Nginx configuration
sudo nano /etc/nginx/sites-available/ammocoin-explorer
```

**Nginx Configuration:**
```nginx
server {
    listen 80;
    server_name explorer.ammocoin.org;

    location / {
        proxy_pass http://localhost:3000;
        proxy_http_version 1.1;
        proxy_set_header Upgrade $http_upgrade;
        proxy_set_header Connection 'upgrade';
        proxy_set_header Host $host;
        proxy_set_header X-Real-IP $remote_addr;
        proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
        proxy_set_header X-Forwarded-Proto $scheme;
        proxy_cache_bypass $http_upgrade;
    }
}
```

```bash
# Enable site
sudo ln -s /etc/nginx/sites-available/ammocoin-explorer /etc/nginx/sites-enabled/
sudo nginx -t
sudo systemctl reload nginx

# Get SSL certificate
sudo certbot --nginx -d explorer.ammocoin.org
```

---

## 🐛 Troubleshooting

### Common Issues

**1. RPC Connection Failed**
```
Error: Failed to connect to AMMOcoin node
```
- Check if `ammocoind` is running
- Verify RPC credentials in `.env.local`
- Check firewall settings
- Ensure RPC is enabled in `ammocoin.conf`

**2. Build Errors**
```
Error: Module not found
```
- Run `rm -rf node_modules package-lock.json`
- Run `npm install`
- Check Node.js version (need 18+)

**3. Performance Issues**
```
Slow page loading or timeouts
```
- Enable `txindex=1` in AMMOcoin node
- Increase RPC timeout in `ammocoin.conf`
- Add more RAM to your server
- Enable caching in production

**4. Styling Issues**
```
CSS not loading correctly
```
- Clear browser cache
- Check if Tailwind CSS built correctly
- Verify `npm run build` completed successfully

### Debug Mode

Enable debug logging:
```bash
# In .env.local
NODE_ENV=development
DEBUG=ammocoin-explorer:*

# Run with debug output
npm run dev
```

### Health Checks

Create a health check endpoint:
```bash
# Check if explorer is responding
curl http://localhost:3000/api/stats

# Check AMMOcoin node
curl -u explorer:password \
     -d '{"jsonrpc":"1.0","id":"test","method":"getblockchaininfo","params":[]}' \
     -H 'content-type: text/plain;' \
     http://localhost:51473/
```

---

## 🔧 Advanced Configuration

### Performance Optimization

**1. Caching Configuration**
```javascript
// next.config.js
const nextConfig = {
  // Enable caching
  experimental: {
    largePageDataBytes: 128 * 1000, // 128KB
  },

  // Image optimization
  images: {
    formats: ['image/webp', 'image/avif'],
  },

  // Compression
  compress: true,
}
```

**2. Database Setup (Optional)**
For better performance, you can add a database layer:
```bash
# Install PostgreSQL
sudo apt install postgresql postgresql-contrib

# Setup database for caching
createdb ammocoin_explorer_cache
```

**3. Redis Cache (Optional)**
```bash
# Install Redis
sudo apt install redis-server

# Configure Redis caching in your application
```

### Monitoring Setup

**1. Application Monitoring**
```bash
# Install monitoring tools
npm install --save @sentry/nextjs
npm install --save newrelic
```

**2. Server Monitoring**
```bash
# Install system monitoring
sudo apt install htop iotop netstat-nat

# Monitor processes
pm2 monit
```

### Security Hardening

**1. Environment Security**
```bash
# Secure file permissions
chmod 600 .env.local
chmod 600 ammocoin.conf

# Use environment variables instead of files
export AMMOCOIN_RPC_PASSWORD="$(openssl rand -base64 32)"
```

**2. Network Security**
```bash
# Configure firewall (Ubuntu)
sudo ufw enable
sudo ufw allow ssh
sudo ufw allow 80
sudo ufw allow 443
sudo ufw deny 51473  # Block external RPC access
```

**3. Content Security Policy**
```javascript
// next.config.js
const nextConfig = {
  async headers() {
    return [
      {
        source: '/(.*)',
        headers: [
          {
            key: 'Content-Security-Policy',
            value: "default-src 'self'; script-src 'self' 'unsafe-eval'; style-src 'self' 'unsafe-inline';"
          }
        ]
      }
    ]
  }
}
```

### Custom Branding

**1. Update Colors**
```css
/* In tailwind.config.ts */
colors: {
  ammocoin: {
    primary: "#your-color",
    hover: "#your-hover-color",
    // ... other colors
  }
}
```

**2. Custom Logo**
```typescript
// Update in src/components/layout/Navbar.tsx
<img src="/your-logo.png" alt="Your Explorer" />
```

**3. Custom Favicon**
Replace files in `/public/`:
- `favicon.ico`
- `icon.png`
- `apple-icon.png`

---

## 📞 Support

### Getting Help

**Documentation:**
- [AMMOcoin Official Docs](https://docs.ammocoin.org)
- [Next.js Documentation](https://nextjs.org/docs)
- [React Documentation](https://react.dev)

**Community:**
- [AMMOcoin Discord](https://discord.gg/ammocoin)
- [GitHub Issues](https://github.com/ammocoin/ammocoin-explorer/issues)
- [AMMOcoin Forum](https://forum.ammocoin.org)

**Professional Support:**
- Enterprise support available
- Custom development services
- Contact: support@ammocoin.org

---

## 📜 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

**Happy Exploring! 🚀**

*Built with ❤️ for the AMMOcoin community*