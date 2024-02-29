import { useEffect, useState } from "react";
import { Container, Table, TableContainer, TableHead, TableRow, TableCell, TableBody, colors } from "@mui/material";
import { BACKEND_URL } from "../../utils";


interface CustomerTotalBalance {
    id: number;
    name: string;
    total_balance: number;
}


export const CustomerBalance = () => {
    const [loading, setLoading] = useState(false);
    const [customer, setCustomer] = useState([])

    useEffect(() => {
        setLoading(true);
        fetch(`${BACKEND_URL}/customer/by-total-balance`).then(response => response.json()).then(data => { setCustomer(data); setLoading(false); });
    }, []);

    return (
        <Container>
            <h2 style={{ textAlign: "left", marginLeft: "12px" }}>Customers sorted based on their total balance</h2>
            {!loading && customer.length === 0 && <div>No customer found.</div>}
            {!loading &&
                customer.length > 0 && (
                    <TableContainer style={{ backgroundColor: colors.grey[50] }}>
                        <Table sx={{ minWidth: 400 }} aria-label="simple table">
                            <TableHead>
                                <TableRow>
                                    <TableCell align="center">#</TableCell>
                                    <TableCell align="center">Customer</TableCell>
                                    <TableCell align="center">Total balance</TableCell>
                                </TableRow>
                            </TableHead>

                            <TableBody>
                                {customer.map((customer_balance: CustomerTotalBalance, index) => (
                                    <TableRow key={customer_balance.id}>
                                        <TableCell align="center" component="th" scope="row">{index + 1}</TableCell>
                                        <TableCell align="center" component="th" scope="row">{customer_balance.name}</TableCell>
                                        <TableCell align="center">{(customer_balance.total_balance == null) ? 0 : customer_balance.total_balance}</TableCell>
                                    </TableRow>
                                ))}
                            </TableBody>
                        </Table>
                    </TableContainer>
                )
            }
        </Container>
    )
}