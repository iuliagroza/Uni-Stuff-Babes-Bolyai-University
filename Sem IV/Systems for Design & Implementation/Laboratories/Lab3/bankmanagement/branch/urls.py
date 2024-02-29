from django.urls import path
from .views import BranchAPIView, BranchByNoOfAccounts

urlpatterns = [
    path("branch", BranchAPIView.as_view()),
    path("branch/<int:pk>", BranchAPIView.as_view()),  # to capture our ids
    path("branch/by-no-of-accounts", BranchByNoOfAccounts.as_view()),
]
