# Contributing to Glasses AI

Welcome to the Glasses AI project! We're excited to have you contribute. This document provides guidelines and instructions to help you get started.

## Development Environment Setup

We've created an automated setup script to make it easy for you to set up your development environment:

```powershell
# Run this from the project root
.\scripts\setup_dev_environment.ps1
```

This script will:
- Verify required software (Git, VSCode/Cursor, PlatformIO)
- Set up Git hooks for code quality
- Install recommended VSCode extensions
- Initialize the PlatformIO project

## Development Workflow

1. **Fork the Repository**: Create your own fork of the project
2. **Create a Branch**: Make a branch for your feature or bugfix
3. **Write Tests**: Follow test-driven development principles
4. **Implement Changes**: Write your code following our style guidelines
5. **Run Tests**: Ensure all tests pass
6. **Create a Pull Request**: Submit your changes for review

## Code Style Guidelines

- Follow the existing code style in the project
- Use meaningful variable and function names
- Keep functions small and focused
- Write appropriate comments for complex logic
- Maintain type safety

## Testing

- Write unit tests for new functionality
- Ensure all tests pass before submitting a PR
- Use TDD where possible
- Run the full test suite before submitting changes

## Pull Request Process

1. Update documentation to reflect any changes
2. Ensure your code passes all tests
3. Make sure your PR addresses only one concern
4. Request review from maintainers
5. Address any feedback from code reviews

## Community Guidelines

- Be respectful and inclusive in all interactions
- Help other contributors when possible
- Report bugs and issues clearly
- Provide constructive feedback

## Getting Help

If you need help with anything, please:
- Check existing documentation
- Look through open/closed issues
- Ask questions in our community channels

Thank you for contributing to Glasses AI! 