import { SetStateAction, useEffect, useState } from "react";
import ReadMoreIcon from "@mui/icons-material/ReadMore"
import EditIcon from "@mui/icons-material/Edit"
import DeleteForeverIcon from "@mui/icons-material/DeleteForever"
import { Container, Table, TableContainer, TableHead, TableRow, TableCell, TableBody, IconButton, Tooltip, colors, Box, Pagination, CssBaseline } from "@mui/material";
import { Link } from "react-router-dom";
import { BACKEND_URL } from "../../utils";
import { CustomerMenu } from "./CustomerMenu";
import { Customer } from "../../models/Customer";
import React from "react";
import { useMediaQuery } from "react-responsive";

export const DisplayCustomerList = () => {
    const [loading, setLoading] = useState(false);
    const [customer, setCustomer] = useState([]);

    const isBigScreen = useMediaQuery({ query: "(min-width: 775px)" });

    useEffect(() => {
        setLoading(true);
        fetch(`${BACKEND_URL}/customer`).then(response => response.json()).then(data => { setCustomer(data); setLoading(false); });
    }, []);

    return (
        <React.Fragment>
            <CssBaseline />

            <CustomerMenu />
            <h1>Customer list</h1>
            {!loading && customer.length === 0 && <div>No customers found.</div>}
            {isBigScreen && !loading &&
                customer.length > 0 && (
                    <>
                        <Table aria-label="simple table">
                            <TableHead>
                                <TableRow>
                                    <TableCell align="center">#</TableCell>
                                    <TableCell align="center">Name</TableCell>
                                    <TableCell align="center">Phone number</TableCell>
                                    <TableCell align="center">Email</TableCell>
                                    <TableCell align="center">Address</TableCell>
                                    <TableCell align="center">Total savings</TableCell>
                                    <TableCell align="center">Total loans</TableCell>
                                </TableRow>
                            </TableHead>

                            <TableBody>
                                {customer.map((customer: any, index) => (
                                    <TableRow key={customer.id}>
                                        <TableCell align="center" component="th" scope="row">{index + 1}</TableCell>
                                        <TableCell align="center">{customer.name}</TableCell>
                                        <TableCell align="center">{customer.phone}</TableCell>
                                        <TableCell align="center">{customer.email}</TableCell>
                                        <TableCell align="center">{customer.address}</TableCell>
                                        <TableCell align="center">{String(customer.total_savings)}</TableCell>
                                        <TableCell align="center">{String(customer.total_loans)}</TableCell>
                                        <TableCell align="center">
                                            <IconButton
                                                component={Link}
                                                sx={{ mr: 1 }}
                                                to={`/customer/${customer.id}/details`}
                                            >
                                                <Tooltip title="View details of customer" arrow>
                                                    <ReadMoreIcon />
                                                </Tooltip>
                                            </IconButton>

                                            <IconButton
                                                component={Link}
                                                sx={{ mr: 1 }}
                                                to={`/customer/${customer.id}/update`}
                                            >
                                                <Tooltip title="Update customer data" arrow>
                                                    <EditIcon />
                                                </Tooltip>
                                            </IconButton>

                                            <IconButton
                                                component={Link}
                                                sx={{ mr: 1 }}
                                                to={`/customer/${customer.id}/delete`}
                                            >
                                                <Tooltip title="Delete customer" arrow>
                                                    <DeleteForeverIcon />
                                                </Tooltip>
                                            </IconButton>
                                        </TableCell>
                                    </TableRow>
                                ))}
                            </TableBody>
                        </Table>
                        <Box sx={{ mt: 2, align: "center" }}>
                            <Pagination
                                color="primary"
                                size="large"
                                siblingCount={2}
                                sx={{ '& .MuiPaginationItem-textPrimary': { color: '#fff' } }}
                                showFirstButton
                                showLastButton
                                boundaryCount={2}
                            />
                        </Box>
                    </>
                )
            }
            {!isBigScreen && !loading &&
                customer.length > 0 && (
                    <>
                        <Table aria-label="simple table">
                            <TableHead>
                                <TableRow>
                                    <TableCell align="center">#</TableCell>
                                    <TableCell align="center">Name</TableCell>
                                </TableRow>
                            </TableHead>

                            <TableBody>
                                {customer.map((customer: any, index) => (
                                    <TableRow key={customer.id}>
                                        <TableCell align="center" component="th" scope="row">{index + 1}</TableCell>
                                        <TableCell align="center">{customer.name}</TableCell>
                                        <TableCell align="center">
                                            <IconButton
                                                component={Link}
                                                sx={{ mr: 3 }}
                                                to={`/customer/${customer.id}/details`}
                                            >
                                                <Tooltip title="View details of customer" arrow>
                                                    <ReadMoreIcon />
                                                </Tooltip>
                                            </IconButton>

                                            <IconButton
                                                component={Link}
                                                sx={{ mr: 3 }}
                                                to={`/customer/${customer.id}/update`}
                                            >
                                                <Tooltip title="Update customer data" arrow>
                                                    <EditIcon />
                                                </Tooltip>
                                            </IconButton>

                                            <IconButton
                                                component={Link}
                                                sx={{ mr: 3 }}
                                                to={`/customer/${customer.id}/delete`}
                                            >
                                                <Tooltip title="Delete customer" arrow>
                                                    <DeleteForeverIcon />
                                                </Tooltip>
                                            </IconButton>
                                        </TableCell>
                                    </TableRow>
                                ))}
                            </TableBody>
                        </Table>
                        <Box sx={{ mt: 2, align: "center" }}>
                            <Pagination
                                color="primary"
                                size="large"
                                siblingCount={2}
                                sx={{ '& .MuiPaginationItem-textPrimary': { color: '#fff' } }}
                                showFirstButton
                                showLastButton
                                boundaryCount={2}
                            />
                        </Box>
                    </>
                )
            }
        </React.Fragment>
    )
}