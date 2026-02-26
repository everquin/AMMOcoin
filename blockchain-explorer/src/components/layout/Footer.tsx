"use client";

import Link from "next/link";
import { Github, ExternalLink, Heart } from "lucide-react";
import { useEffect, useState } from "react";

export function Footer() {
  const currentYear = new Date().getFullYear();
  const [height, setHeight] = useState<number | null>(null);

  useEffect(() => {
    fetch("/api/stats")
      .then((r) => r.json())
      .then((d) => { if (d.success) setHeight(d.data.height); })
      .catch(() => {});
  }, []);

  const footerLinks = [
    {
      title: "Explorer",
      links: [
        { name: "Latest Blocks", href: "/blocks", external: false },
        { name: "Latest Transactions", href: "/transactions", external: false },
        { name: "Network Stats", href: "/stats", external: false },
      ],
    },
    {
      title: "AMMOcoin",
      links: [
        { name: "Official Website", href: "https://ammocoin.org", external: true },
        { name: "Downloads", href: "https://ammocoin.org/downloads", external: true },
        { name: "Whitepaper", href: "https://ammocoin.org/whitepaper", external: true },
      ],
    },
    {
      title: "Development",
      links: [
        { name: "GitHub", href: "https://github.com/everquin/AMMOcoin", external: true },
        { name: "Release Notes", href: "https://github.com/everquin/AMMOcoin/releases", external: true },
        { name: "Build Guide", href: "https://github.com/everquin/AMMOcoin/blob/main/docs/installation/LINUX_BUILD_INSTRUCTIONS_v1.1.0.md", external: true },
      ],
    },
    {
      title: "Network",
      links: [
        { name: "Seed Nodes", href: "https://ammocoin.org", external: true },
        { name: "Genesis Block", href: "/block/0", external: false },
        { name: "API: /api/stats", href: "/api/stats", external: false },
      ],
    },
  ];

  return (
    <footer className="mt-16 border-t border-ammocoin-border">
      <div className="glass-card rounded-none border-0 border-t border-ammocoin-border">
        <div className="container mx-auto px-4 py-12">
          {/* Main Footer Content */}
          <div className="grid grid-cols-1 md:grid-cols-2 lg:grid-cols-5 gap-8">
            {/* Brand Section */}
            <div className="lg:col-span-1">
              <div className="flex items-center space-x-3 mb-4">
                <div className="w-8 h-8 bg-ammocoin-gradient rounded-full flex items-center justify-center font-bold text-ammocoin-black">
                  A
                </div>
                <div className="flex flex-col">
                  <span className="text-lg font-bold text-ammocoin-white">
                    AMMOcoin
                  </span>
                  <span className="text-xs text-ammocoin-primary -mt-1">
                    Explorer
                  </span>
                </div>
              </div>
              <p className="text-ammocoin-gray-400 text-sm mb-4">
                Modern blockchain explorer for AMMOcoin v1.1.0. Explore blocks, transactions, and addresses with privacy-focused features.
              </p>
              <div className="flex space-x-3">
                <a
                  href="https://github.com/everquin/AMMOcoin"
                  target="_blank"
                  rel="noopener noreferrer"
                  className="text-ammocoin-gray-400 hover:text-ammocoin-primary transition-colors"
                  aria-label="GitHub"
                >
                  <Github className="w-5 h-5" />
                </a>
                <a
                  href="https://ammocoin.org"
                  target="_blank"
                  rel="noopener noreferrer"
                  className="text-ammocoin-gray-400 hover:text-ammocoin-primary transition-colors"
                  aria-label="Official Website"
                >
                  <ExternalLink className="w-5 h-5" />
                </a>
              </div>
            </div>

            {/* Footer Links */}
            {footerLinks.map((section) => (
              <div key={section.title} className="lg:col-span-1">
                <h3 className="text-ammocoin-white font-semibold mb-4">
                  {section.title}
                </h3>
                <ul className="space-y-2">
                  {section.links.map((link) => (
                    <li key={link.name}>
                      {link.external ? (
                        <a
                          href={link.href}
                          target="_blank"
                          rel="noopener noreferrer"
                          className="text-ammocoin-gray-400 hover:text-ammocoin-primary transition-colors text-sm flex items-center"
                        >
                          {link.name}
                          <ExternalLink className="w-3 h-3 ml-1" />
                        </a>
                      ) : (
                        <Link
                          href={link.href}
                          className="text-ammocoin-gray-400 hover:text-ammocoin-primary transition-colors text-sm"
                        >
                          {link.name}
                        </Link>
                      )}
                    </li>
                  ))}
                </ul>
              </div>
            ))}
          </div>

          {/* Network Stats Strip */}
          <div className="border-t border-ammocoin-border mt-8 pt-8">
            <div className="grid grid-cols-2 md:grid-cols-4 gap-4 text-center">
              <div className="stat-card">
                <div className="text-2xl font-bold text-ammocoin-primary">
                  {height !== null ? height.toLocaleString() : "..."}
                </div>
                <div className="text-sm text-ammocoin-gray-400">
                  Current Height
                </div>
              </div>
              <div className="stat-card">
                <div className="text-2xl font-bold text-ammocoin-primary">
                  60s
                </div>
                <div className="text-sm text-ammocoin-gray-400">
                  Block Time
                </div>
              </div>
              <div className="stat-card">
                <div className="text-2xl font-bold text-ammocoin-primary">
                  250M
                </div>
                <div className="text-sm text-ammocoin-gray-400">
                  Premine Supply
                </div>
              </div>
              <div className="stat-card">
                <div className="text-2xl font-bold text-ammocoin-primary">
                  PoS
                </div>
                <div className="text-sm text-ammocoin-gray-400">
                  Consensus
                </div>
              </div>
            </div>
          </div>

          {/* Bottom Section */}
          <div className="border-t border-ammocoin-border mt-8 pt-8 flex flex-col md:flex-row justify-between items-center">
            <div className="text-sm text-ammocoin-gray-400 mb-4 md:mb-0">
              &copy; {currentYear} AMMOcoin Explorer. Built with{" "}
              <Heart className="w-4 h-4 inline text-ammocoin-primary" /> for the AMMOcoin community.
            </div>
            <div className="text-sm text-ammocoin-gray-400">
              <span className="mr-4">v1.1.0</span>
              <span className="mr-4">&middot;</span>
              <a
                href="https://ammocoin.org"
                target="_blank"
                rel="noopener noreferrer"
                className="hover:text-ammocoin-primary transition-colors"
              >
                ammocoin.org
              </a>
            </div>
          </div>
        </div>
      </div>
    </footer>
  );
}
