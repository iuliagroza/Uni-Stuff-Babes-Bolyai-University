from django.urls import path
from .views import (
    CustomerAPIView,
    CustomerCSVExportView,
    CustomerFilter,
    CustomerByTotalBalance,
)

urlpatterns = [
    path("customer", CustomerAPIView.as_view()),
    path("customer/<int:pk>", CustomerAPIView.as_view()),  # to capture our ids
    path("customer/filter/<int:val>", CustomerFilter.as_view()),
    path("customer/by-total-balance", CustomerByTotalBalance.as_view()),
    path("export-csv/", CustomerCSVExportView.as_view(), name="export_csv"),
]
