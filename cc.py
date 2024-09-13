# Welcome to the Library of the Future!
# This library has a unique system where each book can be borrowed for a limited period. Let's manage this futuristic inventory.

class Book:
    def __init__(self, title, author):
        self.title = title
        self.author = author
        self.is_borrowed = False

    def __str__(self):
        return f"'{self.title}' by {self.author}"


class FutureLibrary:
    def __init__(self):
        self.books = []

    def add_book(self, book):
        # TODO: Add the book to the library, ensuring no duplicates.

    def remove_book(self, title):
        # TODO: Remove the book by its title if it's not currently borrowed.

    def borrow_book(self, title):
        """
        Borrow a book. If it's already borrowed, indicate that it's unavailable.
        """
        # TODO: Handle the borrowing mechanism.

    def return_book(self, title):
        """
        Return a borrowed book.
        """
        # TODO: Handle the returning mechanism.

    def book_status(self, title):
        """
        Check and display the availability of a book.
        """
        # TODO: Implement the status check.

    def display_books(self):
        # TODO: Display all the books in the library and their borrowing status.

# Instructions for Students:
# 1. Implement the methods in the FutureLibrary class.
# 2. Ensure the integrity of the library, i.e., no duplicate books, and manage the borrowing status correctly.
# 3. After implementing, test your system by:
#    - Adding some Book objects to the FutureLibrary.
#    - Borrowing and returning books and checking their status.
# 4. Challenge:
#    - How would you handle a situation where there's a waiting list for a book? (You don't have to code this, just think about it!)

