/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_printf.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 17:58:38 by llebugle          #+#    #+#             */
/*   Updated: 2024/10/28 12:50:09 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define RESET "\x1b[0m"

static int	test_count = 0;
static int	tests_passed = 0;

void	compare_results(int expected_len, int actual_len, const char *test_name)
{
	test_count++;
	if (expected_len == actual_len)
	{
		tests_passed++;
		printf(GREEN "✓ Test %d passed: %s" RESET "\n", test_count, test_name);
		printf("  Expected length: %d, Actual length: %d\n\n", expected_len,
			actual_len);
	}
	else
	{
		printf(RED "✗ Test %d failed: %s" RESET "\n", test_count, test_name);
		printf("  Expected length: %d, Actual length: %d\n\n", expected_len,
			actual_len);
	}
}

void	print_section_header(const char *section_name)
{
	printf(YELLOW "\n=== Testing %%%s flag ===" RESET "\n\n", section_name);
}

void	test_string_conversion(void)
{
	int printf_len, ft_len;
	char *nul = NULL;
	print_section_header("s");
	// Basic string
	printf("Test: Basic string\n");
	printf_len = printf("++ printf: %s\n", "Hello");
	ft_len = ft_printf("ft_printf: %s\n", "Hello");
	compare_results(printf_len, ft_len, "Basic string test");
	// Empty string
	printf("Test: Empty string\n");
	printf_len = printf("++ printf: '%s'\n", "");
	ft_len = ft_printf("ft_printf: '%s'\n", "");
	compare_results(printf_len, ft_len, "Empty string test");
	// NULL string
	printf("Test: NULL string\n");
	printf_len = printf("++ printf: %s\n", nul);
	ft_len = ft_printf("ft_printf: %s\n", nul);
	compare_results(printf_len, ft_len, "NULL string test");
	// Single character as string
	printf("Test: Single character as string\n");
	printf_len = printf("++ printf: %s\n", "*");
	ft_len = ft_printf("ft_printf: %s\n", "*");
	compare_results(printf_len, ft_len, "Single character string test");
}

void	test_char_conversion(void)
{
	int printf_len, ft_len;
	print_section_header("c");
	// Basic character
	printf("Test: Basic character\n");
	printf_len = printf("++ printf: %c\n", 'A');
	ft_len = ft_printf("ft_printf: %c\n", 'A');
	compare_results(printf_len, ft_len, "Basic character test");
	// Special character
	printf("Test: Special character\n");
	printf_len = printf("++ printf: %c\n", 0);
	ft_len = ft_printf("ft_printf: %c\n", 0);
	compare_results(printf_len, ft_len, "Special character test");
	printf_len = printf("++ printf: %c\n", '*');
	ft_len = ft_printf("ft_printf: %c\n", '*');
	compare_results(printf_len, ft_len, "Special character test");
	printf_len = printf("++ printf: %c\n", '%');
	ft_len = ft_printf("ft_printf: %c\n", '%');
	compare_results(printf_len, ft_len, "Special character test");
}

void	test_combined_conversions(void)
{
	int printf_len, ft_len;
	print_section_header("Combined conversions");
	// String and character combination
	printf("Test: String and character combination\n");
	printf_len = printf("++ printf: %s%c\n", "Test", '!');
	ft_len = ft_printf("ft_printf: %s%c\n", "Test", '!');
	compare_results(printf_len, ft_len,
		"String and character combination test");
	// Multiple characters
	printf("Test: Multiple characters\n");
	printf_len = printf("++ printf: %c%c%c\n", 'A', 'B', 'C');
	ft_len = ft_printf("ft_printf: %c%c%c\n", 'A', 'B', 'C');
	compare_results(printf_len, ft_len, "Multiple characters test");
}

void	test_unsigned_conversion(void)
{
	int printf_len, ft_len;
	print_section_header("u");
	// Basic unsigned int
	printf("Test: Basic unsigned int\n");
	printf_len = printf("++ printf: %u\n", 42);
	ft_len = ft_printf("ft_printf: %u\n", 42);
	compare_results(printf_len, ft_len, "Basic unsigned int test");
	// Zero
	printf("Test: Zero\n");
	printf_len = printf("++ printf: %u\n", 0);
	ft_len = ft_printf("ft_printf: %u\n", 0);
	compare_results(printf_len, ft_len, "Zero test");
	// Negative
	printf("Test: Negative\n");
	printf_len = printf("++ printf: %u\n", -19);
	ft_len = ft_printf("ft_printf: %u\n", -19);
	compare_results(printf_len, ft_len, "Negative test");
	// Maximum unsigned int
	printf("Test: Maximum unsigned int\n");
	printf_len = printf("++ printf: %u\n", 4294967295u);
	ft_len = ft_printf("ft_printf: %u\n", 4294967295u);
	compare_results(printf_len, ft_len, "Maximum unsigned int test");
	// Multiple unsigned ints
	printf("Test: Multiple unsigned ints\n");
	printf_len = printf("++ printf: %u %u %u\n", 42, 0, 4294967295u);
	ft_len = ft_printf("ft_printf: %u %u %u\n", 42, 0, 4294967295u);
	compare_results(printf_len, ft_len, "Multiple unsigned ints test");
}

void	test_pointer_conversion(void)
{
	int		number;
	char	*str;
	void	*ptr_null;

	int printf_len, ft_len;
	number = 42;
	str = "Hello";
	ptr_null = NULL;
	print_section_header("p");
	// Integer pointer
	printf("Test: Integer pointer\n");
	printf_len = printf("++ printf: %p\n", (void *)&number);
	ft_len = ft_printf("ft_printf: %p\n", (void *)&number);
	compare_results(printf_len, ft_len, "Integer pointer test");
	// String pointer
	printf("Test: String pointer\n");
	printf_len = printf("++ printf: %p\n", (void *)str);
	ft_len = ft_printf("ft_printf: %p\n", (void *)str);
	compare_results(printf_len, ft_len, "String pointer test");
	// NULL pointer
	printf("Test: NULL pointer\n");
	printf_len = printf("++ printf: %p\n", ptr_null);
	ft_len = ft_printf("ft_printf: %p\n", ptr_null);
	compare_results(printf_len, ft_len, "NULL pointer test");
	printf("Test: NULL pointer\n");
	printf_len = printf("++ printf: %p, %p\n", (void*)0, ptr_null);
	ft_len = ft_printf("ft_printf: %p, %p\n", (void*)0, ptr_null);
	compare_results(printf_len, ft_len, "NULL pointer test");
	// Multiple pointers
	printf("Test: Multiple pointers\n");
	printf_len = printf("++ printf: %p %p %p\n", (void *)&number, (void *)str,
			ptr_null);
	ft_len = ft_printf("ft_printf: %p %p %p\n", (void *)&number, (void *)str,
			ptr_null);
	compare_results(printf_len, ft_len, "Multiple pointers test");
}

void test_hex_lowercase_conversion(void) {
    int printf_len, ft_len;
    
    print_section_header("x");

    // Basic number
    printf("Test: Basic number\n");
    printf_len = printf("++ printf: %x\n", 42);
    ft_len = ft_printf("ft_printf: %x\n", 42);
    compare_results(printf_len, ft_len, "Basic hex lowercase test");
    printf_len = printf("++ printf: %x\n", 16);
    ft_len = ft_printf("ft_printf: %x\n", 16);
    compare_results(printf_len, ft_len, "Basic hex lowercase test");

    // Zero
    printf("Test: Zero\n");
    printf_len = printf("++ printf: %x\n", 0);
    ft_len = ft_printf("ft_printf: %x\n", 0);
    compare_results(printf_len, ft_len, "Zero hex lowercase test");

    // Large number
    printf("Test: Large number\n");
    printf_len = printf("++ printf: %x\n", 0xDEADBEEF);
    ft_len = ft_printf("ft_printf: %x\n", 0xDEADBEEF);
    compare_results(printf_len, ft_len, "Large hex lowercase test");

    // Multiple numbers
    printf("Test: Multiple numbers\n");
    printf_len = printf("++ printf: %x %x %x\n", 42, 0, 0xDEADBEEF);
    ft_len = ft_printf("ft_printf: %x %x %x\n", 42, 0, 0xDEADBEEF);
    compare_results(printf_len, ft_len, "Multiple hex lowercase test");

    // Small letters
    printf("Test: Small letters\n");
    printf_len = printf("++ printf: %x\n", 0xabcdef);
    ft_len = ft_printf("ft_printf: %x\n", 0xabcdef);
    compare_results(printf_len, ft_len, "Small letters hex test");
}

void test_hex_uppercase_conversion(void) {
    int printf_len, ft_len;
    
    print_section_header("X");

    // Basic number
    printf("Test: Basic number\n");
    printf_len = printf("++ printf: %X\n", 42);
    ft_len = ft_printf("ft_printf: %X\n", 42);
    compare_results(printf_len, ft_len, "Basic hex uppercase test");
    printf_len = printf("++ printf: %X\n", 16);
    ft_len = ft_printf("ft_printf: %X\n", 16);
    compare_results(printf_len, ft_len, "Basic hex uppercase test");

    // Zero
    printf("Test: Zero\n");
    printf_len = printf("++ printf: %X\n", 0);
    ft_len = ft_printf("ft_printf: %X\n", 0);
    compare_results(printf_len, ft_len, "Zero hex uppercase test");

    // Large number
    printf("Test: Large number\n");
    printf_len = printf("++ printf: %X\n", 0xDEADBEEF);
    ft_len = ft_printf("ft_printf: %X\n", 0xDEADBEEF);
    compare_results(printf_len, ft_len, "Large hex uppercase test");

    // Multiple numbers
    printf("Test: Multiple numbers\n");
    printf_len = printf("++ printf: %X %X %X\n", 42, 0, 0xDEADBEEF);
    ft_len = ft_printf("ft_printf: %X %X %X\n", 42, 0, 0xDEADBEEF);
    compare_results(printf_len, ft_len, "Multiple hex uppercase test");

    // Numbers that produce all letters
    printf("Test: All letters\n");
    printf_len = printf("++ printf: %X\n", 0xABCDEF);
    ft_len = ft_printf("ft_printf: %X\n", 0xABCDEF);
    compare_results(printf_len, ft_len, "All letters hex uppercase test");
}

void test_mixed_hex_conversion(void) {
    int printf_len, ft_len;
    
    print_section_header("Mixed x and X");

    // Mix of upper and lowercase hex
    printf("Test: Mixed upper and lowercase\n");
    printf_len = printf("++ printf: %x %X\n", 0xabcdef, 0xABCDEF);
    ft_len = ft_printf("ft_printf: %x %X\n", 0xabcdef, 0xABCDEF);
    compare_results(printf_len, ft_len, "Mixed case hex test");

    // Complex mix
    printf("Test: Complex mix\n");
    printf_len = printf("++ printf: %x-%X-%x-%X\n", 0xabc, 0xABC, 0xdef, 0xDEF);
    ft_len = ft_printf("ft_printf: %x-%X-%x-%X\n", 0xabc, 0xABC, 0xdef, 0xDEF);
    compare_results(printf_len, ft_len, "Complex mixed case hex test");
}

void	additional_test(void)
{
	int printf_len, ft_len;
	int a = 9;
	printf(YELLOW "\n=== Additional ===" RESET "\n");
	printf_len = printf("++ printf: %p\n", &a);
	ft_len = ft_printf("ft_printf: %p\n", &a);
	compare_results(printf_len, ft_len, "Basic unsigned int test");
	}

void	print_test_results(void)
{
	printf(BLUE "\n=== Test Results ===" RESET "\n");
	printf("Total tests: %d\n", test_count);
	printf("Tests passed: " GREEN "%d" RESET "\n", tests_passed);
	printf("Tests failed: " RED "%d" RESET "\n", test_count - tests_passed);
}

int	main(void)
{
	printf(GREEN "=== Starting ft_printf tests ===" RESET "\n");

	test_string_conversion();
	test_char_conversion();
	test_combined_conversions();
	test_unsigned_conversion();
	test_hex_lowercase_conversion();
	test_hex_uppercase_conversion();
	test_mixed_hex_conversion();
	test_pointer_conversion();
	print_test_results();
	//additional_test();

	return (0);
}