from flask import Flask,redirect,url_for,render_template,jsonify
app= Flask(__name__,static_folder='static')

JOBS=[
    {
        'id':'1',
        'title':'Email Spam Classification',
        

    },
    {
        'id':'2',
        'title':'Volship Website',
        

    },
    {
        'id':'3',
        'title':'Code for this Website',
        

    }
    
    ]

@app.route('/')
def Portfolio_K():
    return render_template("home.html",jobs=JOBS,company_name="Keya Private Limited")

@app.route('/api/json')
def jsoned():
    return jsonify(JOBS)
@app.route('/job/<int:job_id>')
def job_url(job_id):
    # Do something with the job ID
    urls = {
        1: 'https://github.com/thekeya/Email_spam',
        2: 'https://github.com/thekeya/Volship-website',
        3: 'https://github.com/thekeya',
    }
    return redirect(urls[job_id])

if __name__=='__main__':
    app.run(host='0.0.0.0',debug=True)

