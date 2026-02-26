"use client";

import { useState } from "react";
import Link from "next/link";
import { Search, Menu, X, Coins, Activity, Users, BarChart3 } from "lucide-react";
import { SearchBar } from "@/components/ui/SearchBar";

export function Navbar() {
  const [isMenuOpen, setIsMenuOpen] = useState(false);

  const toggleMenu = () => {
    setIsMenuOpen(!isMenuOpen);
  };

  const navigation = [
    { name: "Blocks", href: "/blocks", icon: Coins },
    { name: "Transactions", href: "/transactions", icon: Activity },
    { name: "Stats", href: "/stats", icon: BarChart3 },
  ];

  return (
    <nav className="fixed top-0 left-0 right-0 z-50 nav-glass">
      <div className="container mx-auto px-4">
        <div className="flex items-center justify-between h-16">
          {/* Logo */}
          <Link
            href="/"
            className="flex items-center space-x-3 hover:opacity-80 transition-opacity"
          >
            <div className="w-8 h-8 bg-ammocoin-gradient rounded-full flex items-center justify-center font-bold text-ammocoin-black">
              A
            </div>
            <div className="flex flex-col">
              <span className="text-xl font-bold text-ammocoin-white">
                AMMOcoin
              </span>
              <span className="text-xs text-ammocoin-primary -mt-1">
                Explorer
              </span>
            </div>
          </Link>

          {/* Desktop Navigation */}
          <div className="hidden md:flex items-center space-x-8">
            {navigation.map((item) => {
              const IconComponent = item.icon;
              return (
                <Link
                  key={item.name}
                  href={item.href}
                  className="flex items-center space-x-2 text-ammocoin-gray-300 hover:text-ammocoin-primary transition-colors"
                >
                  <IconComponent className="w-4 h-4" />
                  <span>{item.name}</span>
                </Link>
              );
            })}
          </div>

          {/* Search Bar */}
          <div className="hidden lg:block flex-1 max-w-md mx-8">
            <SearchBar placeholder="Search blocks, transactions, addresses..." />
          </div>

          {/* Main Site Link */}
          <div className="hidden md:block">
            <a
              href="https://ammocoin.org"
              target="_blank"
              rel="noopener noreferrer"
              className="btn-ammocoin-outline text-sm py-2 px-4"
            >
              AMMOcoin.org
            </a>
          </div>

          {/* Mobile menu button */}
          <button
            onClick={toggleMenu}
            className="md:hidden p-2 rounded-md text-ammocoin-gray-300 hover:text-ammocoin-primary hover:bg-ammocoin-surface transition-colors"
            aria-label="Toggle menu"
          >
            {isMenuOpen ? (
              <X className="w-6 h-6" />
            ) : (
              <Menu className="w-6 h-6" />
            )}
          </button>
        </div>

        {/* Mobile Search Bar */}
        <div className="lg:hidden pb-4">
          <SearchBar placeholder="Search..." />
        </div>
      </div>

      {/* Mobile Navigation Menu */}
      {isMenuOpen && (
        <div className="md:hidden">
          <div className="px-2 pt-2 pb-3 space-y-1 bg-ammocoin-black/95 backdrop-blur-ammocoin border-t border-ammocoin-border">
            {navigation.map((item) => {
              const IconComponent = item.icon;
              return (
                <Link
                  key={item.name}
                  href={item.href}
                  className="flex items-center space-x-3 px-3 py-2 rounded-md text-ammocoin-gray-300 hover:text-ammocoin-primary hover:bg-ammocoin-surface transition-colors"
                  onClick={() => setIsMenuOpen(false)}
                >
                  <IconComponent className="w-5 h-5" />
                  <span>{item.name}</span>
                </Link>
              );
            })}
            <div className="px-3 py-2">
              <a
                href="https://ammocoin.org"
                target="_blank"
                rel="noopener noreferrer"
                className="btn-ammocoin-outline text-sm py-2 px-4 w-full text-center block"
                onClick={() => setIsMenuOpen(false)}
              >
                Visit AMMOcoin.org
              </a>
            </div>
          </div>
        </div>
      )}
    </nav>
  );
}