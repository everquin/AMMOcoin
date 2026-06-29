/** @type {import('next').NextConfig} */
const nextConfig = {
  // better-sqlite3 is a native Node module — must not be bundled by webpack
  experimental: {
    serverComponentsExternalPackages: ['better-sqlite3'],
  },
};

module.exports = nextConfig;
