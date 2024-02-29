import { Link, useNavigate } from "react-router-dom";
import { Customer } from "../../models/Customer";
import { useState } from "react";
import { BACKEND_URL } from "../../utils";
import { Button, Card, CardContent, Container, IconButton, TextField, FormLabel, colors } from "@mui/material";
import ArrowBackIcon from "@mui/icons-material/ArrowBack";
import { useForm } from "react-hook-form";


export const AddCustomer = () => {
    const navigate = useNavigate();
    const [submitting, setSubmitting] = useState(false);
    const { register, handleSubmit } = useForm<Customer>();

    const addCustomer = async (data: Customer) => {
        setSubmitting(true);
        try {
            const response = await fetch(`${BACKEND_URL}/customer`, {
                method: "POST",
                headers: {
                    "Content-Type": "application/json",
                },
                body: JSON.stringify(data),
            });
            if (response.ok)
                alert("Customer added successfully.");
            else
                alert("Failed to add customer.");
            navigate("/customer");
        } catch (error) {
            console.error(error);
            alert("Failed to add customer.");
        }
        setSubmitting(false);
    };

    return (
        <Container>
            <Card>
                <CardContent>
                    <IconButton component={Link} sx={{ mr: 3 }} to={`/customer`}>
                        <ArrowBackIcon />
                    </IconButton>{" "}
                    <form onSubmit={handleSubmit(addCustomer)} style={{ display: "flex", flexDirection: "column", padding: "8px" }}>
                        <Container sx={{ padding: "3px" }} style={{ display: "flex", flexDirection: "row", justifyContent: "space-around" }}>
                            <FormLabel style={{ marginTop: "15px", fontSize: "18px" }}>
                                Name
                            </FormLabel>
                            <TextField {...register("name")}>
                                id="name"
                                label="Name"
                                variant="outlined"
                            </TextField>
                        </Container>

                        <Container sx={{ padding: "3px" }} style={{ display: "flex", flexDirection: "row", justifyContent: "space-around" }}>
                            <FormLabel style={{ marginTop: "15px", fontSize: "18px" }}>
                                Phone number
                            </FormLabel>
                            <TextField {...register("phone")}>
                                id="phone"
                                label="Phone number"
                                variant="outlined"
                            </TextField>
                        </Container>

                        <Container sx={{ padding: "3px" }} style={{ display: "flex", flexDirection: "row", justifyContent: "space-around" }}>
                            <FormLabel style={{ marginTop: "15px", fontSize: "18px" }}>
                                Email address
                            </FormLabel>
                            <TextField {...register("email")}>
                                id="email"
                                label="Email address"
                                variant="outlined"
                            </TextField>
                        </Container>

                        <Container sx={{ padding: "3px" }} style={{ display: "flex", flexDirection: "row", justifyContent: "space-around" }}>
                            <FormLabel style={{ marginTop: "15px", fontSize: "18px" }}>
                                Address
                            </FormLabel>
                            <TextField {...register("address")}>
                                id="address"
                                label="Address"
                                variant="outlined"
                            </TextField>
                        </Container>

                        <Container sx={{ padding: "3px" }} style={{ display: "flex", flexDirection: "row", justifyContent: "space-around" }}>
                            <FormLabel style={{ marginTop: "15px", fontSize: "18px" }}>
                                Total savings
                            </FormLabel>
                            <TextField {...register("total_savings")}>
                                id="total_savings"
                                label="Total Savings"
                                variant="outlined"
                            </TextField>
                        </Container>

                        <Container sx={{ padding: "3px" }} style={{ display: "flex", flexDirection: "row", justifyContent: "space-around" }}>
                            <FormLabel style={{ marginTop: "15px", fontSize: "18px" }}>
                                Total Loans
                            </FormLabel>
                            <TextField {...register("total_loans")}>
                                id="total_loans"
                                label="Total loans"
                                variant="outlined"
                            </TextField>
                        </Container>

                        <Button type="submit" variant="contained" sx={{ backgroundColor: colors.green[500] }}>Add customer</Button>
                    </form>
                </CardContent>
            </Card>
        </Container>
    );
}