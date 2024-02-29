from rest_framework import status
from rest_framework.test import APITestCase

from bank.models import Bank
from branch.models import Branch
from account.models import Account
from customer.models import Customer
from transaction.models import Transaction


class NonCRUDFunctionalitiesTest(APITestCase):
    @classmethod
    def setUpTestData(cls):
        Bank.objects.create(
            name="Banca Transilvania",
            bicswift="BTRLRO22",
            headquarters="Cluj-Napoca, Cluj, Romania",
            ceo="Omer Tetik",
            total_assets=625000000,
            total_equity=876789,
        )
        Bank.objects.create(
            name="UBS",
            bicswift="UBSCH",
            headquarters="Winterthur, ZH, Switzerland",
            ceo="Sergio Ermotti",
            total_assets=77657899865466,
            total_equity=677868769,
        )
        Bank.objects.create(
            name="BNY Mellon",
            bicswift="NYC99",
            headquarters="NYC, NY, USA",
            ceo="Robin Vince",
            total_assets=656876866576,
            total_equity=876756443,
        )
        Bank.objects.create(
            name="CEC Bank",
            bicswift="CECRO01",
            headquarters="Bucuresti, Romania",
            ceo="Bogdan Neacsu",
            total_assets=6578978,
            total_equity=8688,
        )

        Branch.objects.create(
            name="BTb",
            bicswift="CECRO01",
            address="Cluj-Napoca, Cluj, Romania",
            total_assets=625000000,
            total_equity=876789,
            bank=Bank.objects.get(name="Banca Transilvania"),
        )
        Branch.objects.create(
            name="UBSb",
            bicswift="CECRO01",
            address="Winterthur, ZH, Switzerland",
            total_assets=77657899865466,
            total_equity=677868769,
            bank=Bank.objects.get(name="UBS"),
        )
        Branch.objects.create(
            name="BNYb",
            bicswift="CECRO01",
            address="NYC, NY, USA",
            total_assets=656876866576,
            total_equity=876756443,
            bank=Bank.objects.get(name="BNY Mellon"),
        )
        Branch.objects.create(
            name="CECb",
            bicswift="CECRO01",
            address="Bucuresti, Romania",
            total_assets=6578978,
            total_equity=8688,
            bank=Bank.objects.get(name="CEC Bank"),
        )

        Account.objects.create(
            name="Acc1",
            iban="21eert43f",
            bicswift="BTRLRO22",
            balance=12000,
            currency="RON",
            branch=Branch.objects.get(name="BTb"),
        )
        Account.objects.create(
            name="Acc2",
            iban="e2dfrth54",
            bicswift="BTRLRO22",
            balance=1500,
            currency="RON",
            branch=Branch.objects.get(name="BTb"),
        )
        Account.objects.create(
            name="Acc3",
            iban="2dfvebt5g",
            bicswift="CECRO01",
            balance=99000,
            currency="RON",
            branch=Branch.objects.get(name="CECb"),
        )
        Account.objects.create(
            name="Acc4",
            iban="3f65tgtjg",
            bicswift="NYC99",
            balance=1000000,
            currency="USD",
            branch=Branch.objects.get(name="BNYb"),
        )
        Account.objects.create(
            name="Acc5",
            iban="f3gthtyhn",
            bicswift="UBSCH",
            balance=500000,
            currency="CHF",
            branch=Branch.objects.get(name="UBSb"),
        )
        Account.objects.create(
            name="Acc6",
            iban="34fgthyju",
            bicswift="UBSCH",
            balance=13500000,
            currency="CHF",
            branch=Branch.objects.get(name="UBSb"),
        )

        Customer.objects.create(
            name="Bogdan Popescu",
            phone="+40723778638",
            email="bpopescu@gmail.com",
            address="Bucuresti, Romania",
            total_savings=1500000000,
            total_loans=150000,
        )
        Customer.objects.create(
            name="Maria Dobrescu",
            phone="+40712654444",
            email="mdobrescu@gmail.com",
            address="Bucuresti, Romania",
            total_savings=125000,
            total_loans=500,
        )
        Customer.objects.create(
            name="John Snow",
            phone="+391232425",
            email="jsnow@gmail.com",
            address="NYC, NY, USA",
            total_savings=1233000,
            total_loans=1500000,
        )
        Customer.objects.create(
            name="Mary Jane",
            phone="+302347688",
            email="mjane@gmail.com",
            address="Zurich, ZH, Switzerland",
            total_savings=23000000000,
            total_loans=10,
        )
        Customer.objects.create(
            name="Cornelia Petrescu",
            phone="+40723787879",
            email="cpopescu@gmail.com",
            address="Cluj-Napoca, Cluj, Romania",
            total_savings=5000,
            total_loans=100,
        )

        Transaction.objects.create(
            account=Account.objects.get(name="Acc1"),
            customer=Customer.objects.get(name="Bogdan Popescu"),
            volume=1,
        )

        Transaction.objects.create(
            account=Account.objects.get(name="Acc2"),
            customer=Customer.objects.get(name="Bogdan Popescu"),
            volume=2,
        )

        Transaction.objects.create(
            account=Account.objects.get(name="Acc1"),
            customer=Customer.objects.get(name="Maria Dobrescu"),
            volume=3,
        )

        Transaction.objects.create(
            account=Account.objects.get(name="Acc3"),
            customer=Customer.objects.get(name="Maria Dobrescu"),
            volume=4,
        )

        Transaction.objects.create(
            account=Account.objects.get(name="Acc4"),
            customer=Customer.objects.get(name="John Snow"),
            volume=5,
        )

        Transaction.objects.create(
            account=Account.objects.get(name="Acc5"),
            customer=Customer.objects.get(name="Mary Jane"),
            volume=6,
        )

        Transaction.objects.create(
            account=Account.objects.get(name="Acc6"),
            customer=Customer.objects.get(name="Mary Jane"),
            volume=7,
        )

    def test_filter(self):
        response_billionaire = self.client.get("/api/customer/filter/1000000000")
        self.assertEqual(response_billionaire.status_code, status.HTTP_200_OK)
        self.assertEqual(len(response_billionaire.data), 2)

        response_millionaire = self.client.get("/api/customer/filter/1000000")
        self.assertEqual(response_millionaire.status_code, status.HTTP_200_OK)
        self.assertEqual(len(response_millionaire.data), 3)

        delete_customer1 = self.client.delete("/api/customer/1")
        self.assertEqual(delete_customer1.status_code, status.HTTP_200_OK)

        response_billionaire_del = self.client.get("/api/customer/filter/1000000000")
        self.assertEqual(response_billionaire_del.status_code, status.HTTP_200_OK)
        self.assertEqual(len(response_billionaire_del.data), 1)

        response_no_res = self.client.get("/api/customer/filter/1000000000000")
        self.assertEqual(response_no_res.status_code, status.HTTP_200_OK)
        self.assertEqual(len(response_no_res.data), 0)

    def test_customer_by_total_balance(self):
        response_total_balance = self.client.get("/api/customer/by-total-balance")
        self.assertEqual(response_total_balance.status_code, status.HTTP_200_OK)

        customer1 = response_total_balance.data[0]
        self.assertEqual(customer1["name"], "Mary Jane")
        self.assertEqual(customer1["total_balance"], 14000000)

        customer2 = response_total_balance.data[1]
        self.assertEqual(customer2["name"], "John Snow")
        self.assertEqual(customer2["total_balance"], 1000000)

        customer3 = response_total_balance.data[2]
        self.assertEqual(customer3["name"], "Maria Dobrescu")
        self.assertEqual(customer3["total_balance"], 111000)

        customer4 = response_total_balance.data[3]
        self.assertEqual(customer4["name"], "Bogdan Popescu")
        self.assertEqual(customer4["total_balance"], 13500)

        customer5 = response_total_balance.data[4]
        self.assertEqual(customer5["name"], "Cornelia Petrescu")
        self.assertEqual(customer5["total_balance"], None)
