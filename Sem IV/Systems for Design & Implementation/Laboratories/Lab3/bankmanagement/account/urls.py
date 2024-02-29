from django.urls import path
from .views import AccountAPIView, AccountsByNumberOfCustomers

urlpatterns = [
    path("account", AccountAPIView.as_view()),
    path("account/<int:pk>", AccountAPIView.as_view()),  # to capture our ids
    path("account/by-no-of-customers", AccountsByNumberOfCustomers.as_view()),
]
