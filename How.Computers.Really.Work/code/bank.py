# Define a bank account class in Python.
class BankAccount:
    def __init__(self, balance, name):
        self.balance = balance
        self.name = name

    def withdraw(self, amount):
        self.balance = self.balance - amount

    def deposit(self, amount):
        self.balance = self.balance + amount

# Create a bank account object based on the class.
smithAccount = BankAccount(10.0, 'Harriet Smith')

# Deposit some additional money to the account.
smithAccount.deposit(5.25)

# Print the account balance.
print(smithAccount.balance)
