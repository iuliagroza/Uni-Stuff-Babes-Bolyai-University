from django.urls import path
from .views import BankAPIView, BankByNoOfBranches

urlpatterns = [
    path("bank", BankAPIView.as_view()),
    path("bank/<int:pk>", BankAPIView.as_view()),  # to capture our ids
    path("bank/by-no-of-branches", BankByNoOfBranches.as_view()),
]
