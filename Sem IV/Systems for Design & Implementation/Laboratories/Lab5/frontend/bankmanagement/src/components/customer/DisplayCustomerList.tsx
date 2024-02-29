import { useEffect, useState } from "react";
import { Customer } from "../../models/Customer";
import ReadMoreIcon from "@mui/icons-material/ReadMore"
import EditIcon from "@mui/icons-material/Edit"
import DeleteForeverIcon from "@mui/icons-material/DeleteForever"
import { Container, Table, TableContainer, TableHead, TableRow, TableCell, TableBody, IconButton, Tooltip, colors } from "@mui/material";
import { Link } from "react-router-dom";
import { BACKEND_URL } from "../../utils";


export const DisplayCustomerList = () => {
    const [loading, setLoading] = useState(false);
    const [customer, setCustomer] = useState([])

    useEffect(() => {
        setLoading(true);
        fetch(`${BACKEND_URL}/customer`).then(response => response.json()).then(data => { setCustomer(data); setLoading(false); });
    }, []);

    return (
        <Container>
            <h1>Customer list</h1>
            {!loading && customer.length === 0 && <div>No customers found.</div>}
            {!loading &&
                customer.length > 0 && (
                    <TableContainer style={{ backgroundColor: colors.grey[50] }}>
                        <Table sx={{ minWidth: 850 }} aria-label="simple table">
                            <TableHead>
                                <TableRow>
                                    <TableCell align="center">#</TableCell>
                                    <TableCell align="center">Name</TableCell>
                                    <TableCell align="center">Phone number</TableCell>
                                    <TableCell align="center">Email address</TableCell>
                                    <TableCell align="center">Address</TableCell>
                                    <TableCell align="center">Total Savings</TableCell>
                                    <TableCell align="center">Total Loans</TableCell>
                                    <TableCell>Options</TableCell>
                                </TableRow>
                            </TableHead>

                            <TableBody>
                                {customer.sort((a: Customer, b: Customer) => b.total_savings - a.total_savings).map((customer: Customer, index) => (
                                    <TableRow key={customer.id}>
                                        <TableCell align="center" component="th" scope="row">{index + 1}</TableCell>
                                        <TableCell align="center" component="th" scope="row">
                                            {customer.name}
                                        </TableCell>
                                        <TableCell align="center">{customer.phone}</TableCell>
                                        <TableCell align="center">{customer.email}</TableCell>
                                        <TableCell align="center">{customer.address}</TableCell>
                                        <TableCell align="center">{customer.total_savings}</TableCell>
                                        <TableCell align="center">{customer.total_loans}</TableCell>
                                        <TableCell align="center">
                                            <IconButton
                                                component={Link}
                                                sx={{ mr: 3 }}
                                                to={`/customer/${customer.id}/details`}>
                                                <Tooltip title="View details of customer" arrow>
                                                    <ReadMoreIcon />
                                                </Tooltip>
                                            </IconButton>

                                            <IconButton
                                                component={Link}
                                                sx={{ mr: 3 }}
                                                to={`/customer/${customer.id}/update`}>
                                                <Tooltip title="Update customer data" arrow>
                                                    <EditIcon />
                                                </Tooltip>
                                            </IconButton>

                                            <IconButton
                                                component={Link}
                                                sx={{ mr: 3 }}
                                                to={`/customer/${customer.id}/delete`}>
                                                <Tooltip title="Delete customer" arrow>
                                                    <DeleteForeverIcon />
                                                </Tooltip>
                                            </IconButton>
                                        </TableCell>
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