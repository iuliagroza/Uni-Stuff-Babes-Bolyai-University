from django.urls import path
from .views import BankAPIView

urlpatterns = [
    path("bank", BankAPIView.as_view()),
    path("bank/<int:pk>", BankAPIView.as_view()),  # to capture our ids
]
