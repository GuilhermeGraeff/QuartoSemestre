<!doctype html>
<html>
    <head>
        <title>Respostaszada</title>
        <meta charset = "utf-8">
    </head>
    <body>
        <?php
            $nome = $_POST['nome'];
            $email = $_POST['email'];
            $q1 = $_POST['q1'];
            $q2 = $_POST['q2'];

        ?>
        <p style="font-size: 50px;text-align:center ">Seu nome é: <?= $nome?></p>
        <p style="font-size: 50px;text-align:center ">Seu email é: <?= $email?></p>



    </body>
</html>