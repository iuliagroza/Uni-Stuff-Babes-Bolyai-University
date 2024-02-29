import { Button, Card, CardActions, CardContent, Container, FormLabel, IconButton, TextField, colors } from "@mui/material";
import { Link, useNavigate, useParams } from "react-router-dom";
import { BACKEND_URL } from "../../utils";
import ArrowBackIcon from "@mui/icons-material/ArrowBack";
import { Customer } from "../../models/Customer";
import { useEffect, useState } from "react";


export const UpdateCustomer = () => {
    const { customerId } = useParams<{ customerId: string }>();
    const navigate = useNavigate();
    const [loading, setLoading] = useState(false);

    const [customer, setCustomer] = useState<Customer>({
        id: parseInt(String(customerId)),
        name: "",
        phone: "",
        email: "",
        address: "",
        total_savings: 0,
        total_loans: 0,
        accounts: [],
    });

    useEffect(() => {
        setLoading(true);
        fetch(`${BACKEND_URL}/customer/${customerId}`).then(response => response.json()).then(data => {
            setCustomer(data);
            setLoading(false);
        });
    }, [customerId]);

    const updateCustomer = async (event: { preventDefault: () => void }) => {
        event.preventDefault();
        setLoading(true);
        fetch(`${BACKEND_URL}/customer/${customerId}`, {
            method: 'PUT',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify(customer)
        }).then(response => {
            if (response.ok) {
                alert("Customer updated successfully.");
            } else {
                console.error('Error updating customer:', response.statusText);
            }
            navigate(`/customer/`);
            setLoading(false);
        }).catch(error => {
            console.error('Error updating customer:', error);
            setLoading(false);
        });
    }

    const handleCancel = (event: { preventDefault: () => void }) => {
        event.preventDefault();
        navigate("/customer");
    };

    return (
        <Container>
            <Card>
                <CardContent>
                    <IconButton component={Link} sx={{ mr: 3 }} to={`/customer`}>
                        <ArrowBackIcon />
                    </IconButton>{" "}
                    <form onSubmit={updateCustomer} style={{ display: "flex", flexDirection: "column", padding: "8px" }}>
                        <Container sx={{ padding: "3px" }} style={{ display: "flex", flexDirection: "row", justifyContent: "space-around" }}>
                            <FormLabel style={{ marginTop: "15px", fontSize: "18px" }}>
                                Name
                            </FormLabel>
                            <TextField
                                id="name"
                                variant="outlined"
                                onChange={(event) => setCustomer({ ...customer, name: event.target.value })}
                            />
                        </Container>

                        <Container sx={{ padding: "3px" }} style={{ display: "flex", flexDirection: "row", justifyContent: "space-around" }}>
                            <FormLabel style={{ marginTop: "15px", fontSize: "18px" }}>
                                Phone number
                            </FormLabel>
                            <TextField
                                id="phone"
                                variant="outlined"
                                onChange={(event) => setCustomer({ ...customer, phone: event.target.value })}
                            />
                        </Container>

                        <Container sx={{ padding: "3px" }} style={{ display: "flex", flexDirection: "row", justifyContent: "space-around" }}>
                            <FormLabel style={{ marginTop: "15px", fontSize: "18px" }}>
                                Email address
                            </FormLabel>
                            <TextField
                                id="email"
                                variant="outlined"
                                onChange={(event) => setCustomer({ ...customer, email: event.target.value })}
                            />
                        </Container>

                        <Container sx={{ padding: "3px" }} style={{ display: "flex", flexDirection: "row", justifyContent: "space-around" }}>
                            <FormLabel style={{ marginTop: "15px", fontSize: "18px" }}>
                                Address
                            </FormLabel>
                            <TextField
                                id="address"
                                variant="outlined"
                                onChange={(event) => setCustomer({ ...customer, address: event.target.value })}
                            />
                        </Container>

                        <Container sx={{ padding: "3px" }} style={{ display: "flex", flexDirection: "row", justifyContent: "space-around" }}>
                            <FormLabel style={{ marginTop: "15px", fontSize: "18px" }}>
                                Total savings
                            </FormLabel>
                            <TextField
                                id="total_savings"
                                variant="outlined"
                                onChange={(event) => setCustomer({ ...customer, total_savings: parseInt(event.target.value) })}
                            />
                        </Container>

                        <Container sx={{ padding: "3px" }} style={{ display: "flex", flexDirection: "row", justifyContent: "space-around" }}>
                            <FormLabel style={{ marginTop: "15px", fontSize: "18px" }}>
                                Total loans
                            </FormLabel>
                            <TextField
                                id="total_loans"
                                variant="outlined"
                                onChange={(event) => setCustomer({ ...customer, total_loans: parseInt(event.target.value) })}
                            />
                        </Container>
                    </form>
                </CardContent>
                <CardActions sx={{ justifyContent: "center" }}>
                    <Button type="submit" onClick={updateCustomer} variant="contained" sx={{ backgroundColor: colors.green[500] }}>Update customer</Button>
                    <Button onClick={handleCancel} variant="contained" sx={{ backgroundColor: colors.green[500] }}>Cancel</Button>
                </CardActions>
            </Card>
        </Container>
    );
}