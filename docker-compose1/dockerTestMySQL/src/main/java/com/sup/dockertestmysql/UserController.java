package com.sup.dockertestmysql;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
@RequestMapping("/user")
public class UserController {

    @Autowired
    JdbcTemplate jdbcTemplate;
@RequestMapping("/userlist")
    public Object getUsers(){
        return jdbcTemplate.queryForList("select * from users");
    }
}
