#include <string>

namespace ui {
    std::string StudentHTML = R"HTML(
<html>
<head>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link href="https://unpkg.com/layui@2.9.20/dist/css/layui.css" rel="stylesheet">
</head>
<body>
  <script src="https://unpkg.com/vue@3/dist/vue.global.js"></script>
  <script src="https://unpkg.com/layui@2.9.20/dist/layui.js"></script>
    <div id="app">
        <div style="margin: 15px;">
            <button class="layui-btn" onclick="window.changeToIndex()">返回主页</button>
            <br>
            <br>
            <div class="layui-form">
                <select lay-filter="class-select-filter">
                  <option value="">请选择</option>
                  <option v-for="i in classList" :value="i" :key="i">{{ i }}</option>
                </select>
            </div>
            <br>
            <button class="layui-btn" @click="loadData">加载</button>
            <button class="layui-btn layui-btn-normal" @click="addClass">新建班级</button>
            <button class="layui-btn layui-btn-danger" @click="deleteClass">删除班级</button>
        </div>
    </div>

    <script>
    let selectClass = "";
    const { createApp } = Vue
  
    createApp({
        data() {
          return {
            classList: []
        }},
        methods: {
            loadData()
            {
                console.info(selectClass);
            },
            addClass()
            {
                var that = this;
                layer.prompt({title: '请输入要添加的班级名（例如软国2407）：'}, async function(value, index, elem){
                    if(value === '') return elem.focus();
                    await window.addClass(value);
                    layer.msg("添加成功！");
                    that.loadClass();
                    layer.close(index);
                });
            },
            async loadClass()
            {
                var i = await window.getClass();
                this.classList = i.data;
                console.info(this.classList);
                this.$nextTick(() => {
                    layui.form.render('select');
                });
            },
            async deleteClass()
            {
                if(selectClass == "")
                {
                    layer.msg("请至少选择一个班级");
                    return;
                }
                await window.removeClass(selectClass);
                this.loadClass();
                selectClass = "";
            }
        },
        mounted() {
            this.loadClass();
        }
    }).mount('#app');

    layui.use(function(){

var form = layui.form;
var layer = layui.layer;
form.on('select(class-select-filter)', function(data){
  var value = data.value;
  selectClass = value;
});
});
</script>
</body>
</html>
)HTML";
}