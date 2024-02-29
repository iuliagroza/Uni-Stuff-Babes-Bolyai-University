import { SetStateAction, useEffect, useState } from "react";
import ReadMoreIcon from "@mui/icons-material/ReadMore"
import EditIcon from "@mui/icons-material/Edit"
import DeleteForeverIcon from "@mui/icons-material/DeleteForever"
import { Container, Table, TableContainer, TableHead, TableRow, TableCell, TableBody, IconButton, Tooltip, colors, Box, Pagination, CssBaseline } from "@mui/material";
import { Link } from "react-router-dom";
import { BACKEND_URL } from "../../utils";
import { BankMenu } from "./BankMenu";
import { Bank } from "../../models/Bank";
import React from "react";
import { useMediaQuery } from "react-responsive";

export const DisplayBankList = () => {
    const [loading, setLoading] = useState(false);
    const [bank, setBank] = useState([]);

    const isBigScreen = useMediaQuery({ query: "(min-width: 775px)" });

    useEffect(() => {
        setLoading(true);
        fetch(`${BACKEND_URL}/bank`).then(response => response.json()).then(data => { setBank(data); setLoading(false); });
    }, []);

    return (
        <React.Fragment>
            <CssBaseline />

            <BankMenu />
            <h1>Bank list</h1>
            {!loading && bank.length === 0 && <div>No banks found.</div>}
            {isBigScreen && !loading &&
                bank.length > 0 && (
                    <><Table aria-label="simple table">
                        <TableHead>
                            <TableRow>
                                <TableCell align="center">#</TableCell>
                                <TableCell align="center">Name</TableCell>
                                <TableCell align="center">BIC/SWIFT</TableCell>
                                <TableCell align="center">Headquarters</TableCell>
                                <TableCell align="center">CEO</TableCell>
                                <TableCell align="center">Total assets</TableCell>
                                <TableCell align="center">Total equity</TableCell>
                            </TableRow>
                        </TableHead>

                        <TableBody>
                            {bank.map((bank: any, index) => (
                                <TableRow key={bank.id}>
                                    <TableCell align="center" component="th" scope="row">{index + 1}</TableCell>
                                    <TableCell align="center">{bank.name}</TableCell>
                                    <TableCell align="center">{bank.bicswift}</TableCell>
                                    <TableCell align="center">{bank.headquarters}</TableCell>
                                    <TableCell align="center">{bank.ceo}</TableCell>
                                    <TableCell align="center">{String(bank.total_assets)}</TableCell>
                                    <TableCell align="center">{String(bank.total_equity)}</TableCell>
                                    <TableCell align="center">
                                        <Box display="flex" justifyContent="center">
                                            <IconButton
                                                component={Link}
                                                sx={{ mr: 1 }}
                                                to={`/bank/${bank.id}/details`}
                                            >
                                                <Tooltip title="View details of bank" arrow>
                                                    <ReadMoreIcon />
                                                </Tooltip>
                                            </IconButton>

                                            <IconButton
                                                component={Link}
                                                sx={{ mr: 1 }}
                                                to={`/bank/${bank.id}/update`}
                                            >
                                                <Tooltip title="Update bank data" arrow>
                                                    <EditIcon />
                                                </Tooltip>
                                            </IconButton>

                                            <IconButton
                                                component={Link}
                                                to={`/bank/${bank.id}/delete`}
                                            >
                                                <Tooltip title="Delete bank" arrow>
                                                    <DeleteForeverIcon />
                                                </Tooltip>
                                            </IconButton>
                                        </Box>
                                    </TableCell>
                                    <TableCell align="center">
                                        <IconButton
                                            component={Link}
                                            sx={{ fontSize: 13, color: '#000' }}
                                            to={`/user-profile/${bank?.user?.id}`}>
                                            {bank?.user?.username}
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
                bank.length > 0 && (
                    <>
                        <Table aria-label="simple table">
                            <TableHead>
                                <TableRow>
                                    <TableCell align="center">#</TableCell>
                                    <TableCell align="center">Name</TableCell>
                                </TableRow>
                            </TableHead>

                            <TableBody>
                                {bank.map((bank: any, index) => (
                                    <TableRow key={bank.id}>
                                        <TableCell align="center" component="th" scope="row">{index + 1}</TableCell>
                                        <TableCell align="center">{bank.name}</TableCell>
                                        <TableCell align="center">
                                            <IconButton
                                                component={Link}
                                                sx={{ mr: 3 }}
                                                to={`/bank/${bank.id}/details`}
                                            >
                                                <Tooltip title="View details of bank" arrow>
                                                    <ReadMoreIcon />
                                                </Tooltip>
                                            </IconButton>

                                            <IconButton
                                                component={Link}
                                                sx={{ mr: 3 }}
                                                to={`/bank/${bank.id}/update`}
                                            >
                                                <Tooltip title="Update bank data" arrow>
                                                    <EditIcon />
                                                </Tooltip>
                                            </IconButton>

                                            <IconButton
                                                component={Link}
                                                sx={{ mr: 3 }}
                                                to={`/bank/${bank.id}/delete`}
                                            >
                                                <Tooltip title="Delete bank" arrow>
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