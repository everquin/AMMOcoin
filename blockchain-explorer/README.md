# AMMOcoin Explorer

**Modern blockchain explorer for AMMOcoin v1.1.0 with AMMOcoin design system**

[![Version](https://img.shields.io/badge/version-1.1.0-brightgreen)](https://github.com/ammocoin/ammocoin-explorer)
[![Framework](https://img.shields.io/badge/framework-Next.js_16-blue)](https://nextjs.org/)
[![License](https://img.shields.io/badge/license-MIT-yellow)](https://opensource.org/licenses/MIT)

---

## 🚀 Features

### **Blockchain Explorer**
- **Real-time blockchain data** - Live blocks, transactions, and network statistics
- **Advanced search** - Search by block height, transaction hash, or address
- **Privacy transactions** - Full support for Sapling shielded transactions
- **Masternode monitoring** - Track masternode network and rewards
- **Network statistics** - Comprehensive blockchain metrics and analytics

### **Modern Design System**
- **AMMOcoin branding** - Authentic lime green (#32cd32) and black theme
- **Glassmorphism UI** - Modern glass effects with backdrop blur
- **Responsive design** - Perfect on mobile, tablet, and desktop
- **Accessibility** - WCAG compliant with keyboard navigation
- **Performance optimized** - Fast loading with optimized assets

### **Technical Features**
- **TypeScript** - Full type safety and IntelliSense
- **Next.js 16** - Latest React framework with app router
- **Tailwind CSS** - Utility-first styling with custom design tokens
- **Server-side rendering** - SEO optimized with fast page loads
- **Static export ready** - Can be deployed as static site

---

## 📦 Quick Start

### Automated Setup (Recommended)

Use our interactive setup script for the easiest installation:

```bash
# Clone the repository
git clone https://github.com/ammocoin/ammocoin-explorer.git
cd ammocoin-explorer

# Run the setup script
./setup.sh
```

The setup script will:
- Check prerequisites (Node.js 18+, npm, git)
- Install dependencies automatically
- Create environment configuration
- Test AMMOcoin node connection
- Start development server or build for production

### Manual Setup

```bash
# Clone the repository
git clone https://github.com/ammocoin/ammocoin-explorer.git
cd ammocoin-explorer

# Install dependencies
npm install

# Copy environment template
cp .env.example .env.local

# Edit configuration (see DEPLOYMENT_GUIDE.md)
nano .env.local

# Start development server
npm run dev

# Open browser to http://localhost:3000
```

### Prerequisites
- **Node.js 18+** - [Download here](https://nodejs.org/)
- **npm or yarn** - Package manager
- **AMMOcoin Node** - Running `ammocoind` with RPC enabled

📖 **For detailed setup instructions, see [DEPLOYMENT_GUIDE.md](DEPLOYMENT_GUIDE.md)**

### Production Build

```bash
# Build for production
npm run build

# Start production server
npm start
```

### Static Export

```bash
# Enable static export in next.config.js
# Uncomment the following lines:
# output: 'export',
# trailingSlash: true,
# distDir: 'out',

# Build static version
npm run build

# Deploy 'out' directory to any static host
```

---

## 🏗️ Project Structure

```
ammocoin-explorer/
├── src/
│   ├── app/                    # Next.js app router pages
│   │   ├── globals.css        # Global styles with AMMOcoin design
│   │   ├── layout.tsx         # Root layout component
│   │   └── page.tsx          # Homepage
│   ├── components/            # React components
│   │   ├── layout/           # Layout components (Navbar, Footer)
│   │   ├── ui/               # Reusable UI components
│   │   ├── blocks/           # Block-related components
│   │   ├── transactions/     # Transaction components
│   │   └── addresses/        # Address components
│   ├── lib/                  # Utility libraries
│   └── types/                # TypeScript type definitions
├── public/                   # Static assets
├── tailwind.config.ts        # Tailwind configuration
├── next.config.js           # Next.js configuration
└── package.json            # Dependencies and scripts
```

---

## 🎨 Design System

### **Color Palette**
```css
--ammocoin-primary: #32cd32     /* Lime green */
--ammocoin-hover: #5bd75b       /* Lighter green */
--ammocoin-black: #000000       /* Pure black */
--ammocoin-white: #ffffff       /* Pure white */
--ammocoin-surface: rgba(255, 255, 255, 0.05)  /* Glass surface */
```

### **Typography**
- **Primary**: Play (Headers and navigation)
- **Secondary**: Jura (Body text and labels)
- **Monospace**: Inconsolata (Addresses and hashes)

### **Components**
- **Glass cards** - `.glass-card` class
- **Button styles** - `.btn-ammocoin` and `.btn-ammocoin-outline`
- **Search inputs** - `.search-input` class
- **Status badges** - `.status-confirmed`, `.status-pending`, `.status-failed`
- **Hash displays** - `.hash-display` class

---

## 🔧 Configuration

### **Environment Variables**
Create a `.env.local` file:

```bash
# AMMOcoin RPC Configuration
# AMMOcoin v1.1.0 Mainnet RPC Port: 51473
AMMOCOIN_RPC_URL=http://localhost:51473
AMMOCOIN_RPC_USER=your_rpc_user
AMMOCOIN_RPC_PASSWORD=your_rpc_password

# Explorer Configuration
NEXT_PUBLIC_EXPLORER_NAME="AMMOcoin Explorer"
NEXT_PUBLIC_NETWORK_NAME="AMMOcoin Mainnet"
NEXT_PUBLIC_COIN_SYMBOL="AMMO"

# Optional: External APIs
NEXT_PUBLIC_COINMARKETCAP_API_KEY=your_cmc_api_key
```

### **Connecting to AMMOcoin Node**

1. **Configure ammocoind** - Add to `ammocoin.conf`:
   ```ini
   server=1
   rpcuser=explorer
   rpcpassword=secure_password
   rpcallowip=127.0.0.1
   # rpcport=51473  # Optional - 51473 is the default for v1.1.0 mainnet
   ```

2. **Update API endpoints** - Modify `src/lib/api.ts` with your node details

3. **Start your node**:
   ```bash
   ./ammocoind -daemon
   ```

---

## 🚀 Deployment

📖 **For comprehensive deployment instructions, see [DEPLOYMENT_GUIDE.md](DEPLOYMENT_GUIDE.md)**

### **Vercel (Recommended)**
```bash
# Install Vercel CLI
npm i -g vercel

# Deploy
vercel

# Configure environment variables in Vercel dashboard
```

### **Netlify**
```bash
# Build command: npm run build
# Publish directory: out (if using static export)
```

### **Docker**
```dockerfile
FROM node:18-alpine
WORKDIR /app
COPY package*.json ./
RUN npm ci --only=production
COPY . .
RUN npm run build
EXPOSE 3000
CMD ["npm", "start"]
```

### **Static Hosting (Cloudflare Pages)**
1. Enable static export in `next.config.js`
2. Run `npm run build`
3. Upload `out/` directory to Cloudflare Pages

---

## 🛠️ Development

### **Available Scripts**
```bash
npm run dev          # Start development server
npm run build        # Build for production
npm run start        # Start production server
npm run lint         # Run ESLint
npm run type-check   # Run TypeScript checks
```

### **Adding New Features**

1. **API Integration**:
   ```typescript
   // src/lib/api/blocks.ts
   export async function getLatestBlocks() {
     // Implement blockchain API calls
   }
   ```

2. **New Components**:
   ```tsx
   // src/components/blocks/BlockCard.tsx
   export function BlockCard({ block }: { block: Block }) {
     // Component implementation
   }
   ```

3. **New Pages**:
   ```tsx
   // src/app/block/[height]/page.tsx
   export default function BlockPage({ params }: { params: { height: string } }) {
     // Page implementation
   }
   ```

### **Testing**
```bash
# Install testing dependencies
npm install --save-dev jest @testing-library/react

# Run tests
npm test
```

---

## 📚 API Reference

### **Blockchain Data Types**
```typescript
interface Block {
  hash: string;
  height: number;
  timestamp: number;
  transactions: Transaction[];
  // ... see src/types/blockchain.ts
}

interface Transaction {
  txid: string;
  inputs: TransactionInput[];
  outputs: TransactionOutput[];
  // ... complete type definitions
}
```

### **Component Props**
```typescript
// Search Bar
interface SearchBarProps {
  placeholder?: string;
  onSearch?: (query: string) => void;
}

// Block Card
interface BlockCardProps {
  block: Block;
  showDetails?: boolean;
}
```

---

## 🤝 Contributing

We welcome contributions! Please see our [Contributing Guide](CONTRIBUTING.md) for:
- Code standards and style guide
- Pull request process
- Issue reporting guidelines
- Development workflow

### **Code Style**
- **TypeScript** - Strict mode enabled
- **ESLint** - Extended from Next.js config
- **Prettier** - Consistent formatting
- **Conventional Commits** - Semantic commit messages

### **Testing Requirements**
- Unit tests for utilities and hooks
- Component testing with React Testing Library
- E2E tests for critical user flows

---

## 🔒 Security

### **Reporting Vulnerabilities**
Email security issues to: security@ammocoin.org

**Do not create public issues for security vulnerabilities.**

### **Security Features**
- **Input sanitization** - All user inputs sanitized
- **XSS protection** - Content Security Policy enabled
- **HTTPS only** - Secure connections required
- **No private keys** - Read-only blockchain access

---

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

## 🌟 Acknowledgments

- **AMMOcoin Core Team** - Blockchain development
- **Bitcoin & PIVX** - Foundational technologies
- **Next.js Team** - Amazing React framework
- **Tailwind CSS** - Utility-first styling
- **Vercel** - Hosting and deployment

---

## 📞 Support

- **GitHub Issues**: [Report bugs and feature requests](https://github.com/ammocoin/ammocoin-explorer/issues)
- **Discord**: [Join our community](https://discord.gg/ammocoin)
- **Email**: explorer@ammocoin.org
- **Documentation**: [Full documentation](https://docs.ammocoin.org/explorer)

---

**Current Version**: v1.1.0
**Compatible with**: AMMOcoin v1.1.0+
**Status**: Production Ready ✅