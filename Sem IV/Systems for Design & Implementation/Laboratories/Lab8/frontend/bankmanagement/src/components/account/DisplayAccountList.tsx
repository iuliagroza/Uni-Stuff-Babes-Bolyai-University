import { SetStateAction, useEffect, useState } from "react";
import ReadMoreIcon from "@mui/icons-material/ReadMore"
import EditIcon from "@mui/icons-material/Edit"
import DeleteForeverIcon from "@mui/icons-material/DeleteForever"
import { Container, Table, TableContainer, TableHead, TableRow, TableCell, TableBody, IconButton, Tooltip, colors, Box, Pagination, CssBaseline } from "@mui/material";
import { Link } from "react-router-dom";
import { BACKEND_URL } from "../../utils";
import { AccountMenu } from "./AccountMenu";
import { Account } from "../../models/Account";
import React from "react";
import { useMediaQuery } from "react-responsive";

export const DisplayAccountList = () => {
    const [loading, setLoading] = useState(false);
    const [account, setAccount] = useState([]);

    const isBigScreen = useMediaQuery({ query: "(min-width: 775px)" });

    useEffect(() => {
        setLoading(true);
        fetch(`${BACKEND_URL}/account`).then(response => response.json()).then(data => { setAccount(data); setLoading(false); });
    }, []);

    return (
        <React.Fragment>
            <CssBaseline />

            <AccountMenu />
            <h1>Account list</h1>
            {!loading && account.length === 0 && <div>No accounts found.</div>}
            {isBigScreen && !loading &&
                account.length > 0 && (
                    <><TableContainer style={{ backgroundColor: colors.grey[50] }}>
                        <Table sx={{ minWidth: 850 }} aria-label="simple table">
                            <TableHead>
                                <TableRow>
                                    <TableCell align="center">#</TableCell>
                                    <TableCell align="center">Name</TableCell>
                                    <TableCell align="center">IBAN</TableCell>
                                    <TableCell align="center">BIC/SWIFT</TableCell>
                                    <TableCell align="center">Balance</TableCell>
                                    <TableCell align="center">Currency</TableCell>
                                </TableRow>
                            </TableHead>

                            <TableBody>
                                {account.map((account: any, index) => (
                                    <TableRow key={account.id}>
                                        <TableCell align="center" component="th" scope="row">{index + 1}</TableCell>
                                        <TableCell align="center">{account.name}</TableCell>
                                        <TableCell align="center">{account.iban}</TableCell>
                                        <TableCell align="center">{account.bicswift}</TableCell>
                                        <TableCell align="center">{String(account.balance)}</TableCell>
                                        <TableCell align="center">{account.currency}</TableCell>
                                        <TableCell align="center">
                                            <IconButton
                                                component={Link}
                                                sx={{ mr: 1 }}
                                                to={`/account/${account.id}/details`}>
                                                <Tooltip title="View details of account" arrow>
                                                    <ReadMoreIcon />
                                                </Tooltip>
                                            </IconButton>

                                            <IconButton
                                                component={Link}
                                                sx={{ mr: 1 }}
                                                to={`/account/${account.id}/update`}>
                                                <Tooltip title="Update account data" arrow>
                                                    <EditIcon />
                                                </Tooltip>
                                            </IconButton>

                                            <IconButton
                                                component={Link}
                                                sx={{ mr: 1 }}
                                                to={`/account/${account.id}/delete`}>
                                                <Tooltip title="Delete account" arrow>
                                                    <DeleteForeverIcon />
                                                </Tooltip>
                                            </IconButton>
                                        </TableCell>
                                        <TableCell align="center">
                                            <IconButton
                                                component={Link}
                                                sx={{ fontSize: 13, color: '#000' }}
                                                to={`/user-profile/${account?.user?.id}`}>
                                                {account?.user?.username}
                                            </IconButton>
                                        </TableCell>
                                    </TableRow>
                                ))}
                            </TableBody>
                        </Table>
                    </TableContainer>
                        <Box sx={{ mt: 2, textAlign: "center" }}>
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
                account.length > 0 && (
                    <>
                        <Table aria-label="simple table">
                            <TableHead>
                                <TableRow>
                                    <TableCell align="center">#</TableCell>
                                    <TableCell align="center">Name</TableCell>
                                </TableRow>
                            </TableHead>

                            <TableBody>
                                {account.map((account: any, index) => (
                                    <TableRow key={account.id}>
                                        <TableCell align="center" component="th" scope="row">{index + 1}</TableCell>
                                        <TableCell align="center">{account.name}</TableCell>
                                        <TableCell align="center">
                                            <IconButton
                                                component={Link}
                                                sx={{ mr: 3 }}
                                                to={`/account/${account.id}/details`}
                                            >
                                                <Tooltip title="View details of account" arrow>
                                                    <ReadMoreIcon />
                                                </Tooltip>
                                            </IconButton>

                                            <IconButton
                                                component={Link}
                                                sx={{ mr: 3 }}
                                                to={`/account/${account.id}/update`}
                                            >
                                                <Tooltip title="Update account data" arrow>
                                                    <EditIcon />
                                                </Tooltip>
                                            </IconButton>

                                            <IconButton
                                                component={Link}
                                                sx={{ mr: 3 }}
                                                to={`/account/${account.id}/delete`}
                                            >
                                                <Tooltip title="Delete account" arrow>
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