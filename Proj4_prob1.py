#importing matplotlib.pyplot as plb to be able to get library
#to be able to plot a pie chart
import matplotlib.pyplot as plt

#main()
def main():
    #opening the file with "r" to only read the file
    expenses = open("expenses.txt", "r")
    file_content = expenses.read()

    #splitting the file contents by spaces in between the values
    file_content_list = file_content.split(' ')

    #converting the tuple into a list
    list_expense = list(file_content_list)

    #labels for the pie chart
    slice_labels = ['Rent', 'Gas', 'Food', 'Clothing', 'Car payment', 'Misc']

    #plotting and adding in the labels and title
    plt.pie(list_expense, labels=slice_labels)
    plt.title('Expenses')

    plt.show()

#calling main()
main()
