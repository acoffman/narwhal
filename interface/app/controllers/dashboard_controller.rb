class DashboardController < ApplicationController
  
  use_google_charts

  # GET /dashboard
  def index
    @page_title = "Firewall Performance Overview"
    @test_num = params[:test_num]
    @test_num ||= 55
    @nav_over = "current"
    dataset5 = GoogleChartDataset.new :data => [0,100]
    dataset6 = GoogleChartDataset.new :data => [@test_num, @test_num], :color => '0000FF', :title => 'Allowable Average Rate'
    dataset3 = GoogleChartDataset.new :data => [0,100]
    dataset4 = GoogleChartDataset.new :data => [75, 75], :color => 'FF0000', :title => 'Allowable Peak Rate'
    dataset1 = GoogleChartDataset.new :data => [0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100]
    dataset2 = GoogleChartDataset.new :data => [10, 50, 24, 10, 26, 32, 45, 43, 23, 42, 65], :color => '000000', :title => 'Traffic'
    @chart = init_chart("Incoming Traffic Average Rates", [dataset1, dataset2, dataset3, dataset4, dataset5, dataset6])
    	
  	respond_to do |format|
  	  format.html { render :overview }
    end
  end

  def edit_num
    @test_num = params[:value]
    render :text => @test_num
  end

  # GET /dashboard/ip
  def ip          
    @blocked = Blocked.new
  	@blocked.protocols << Protocol.new
  	    
    @blockeds  = Blocked.all
    @protocols = Protocol.all
  
    if params[:proto_list]
      Protocol.find(params[:proto_list]).destroy
    elsif params[:ip_list]
      @blocked  = Blocked.find(params[:ip_list])
      @blocked.destroy
    end
    
    respond_to do |format|
      @nav_ip = "current"
      format.html { render :action => 'ip' }
      format.js
    end
  end

  # DELETE /dashboard/ip/1
#  def destroy which
    # if which == "blocked"
    #   Blocked.find(params[:proto_list]).destroy
    # elsif which == "proto"
    #   Protocol.find(params[:proto_list]).destroy
    # end
    # 
    # redirect_to :action => 'ip' 
#  end

  # POST /dashboard
  def create
    @blocked = Blocked.new( :ip => params[:blocked][:ip], :port => params[:blocked][:port] )
    @blocked.protocols << Protocol.new( :name => params[:blocked][:protocols] )
  
    respond_to do |format|
      if @blocked.save
        format.html { redirect_to :action => 'ip' }
      end
    end
  end

  # GET /dashboard/protocols
  def protocols
    @page_title = "Protocol Configuration"
    @nav_proto = "current"
    render :protocols
  end

  def move_item
    protocol = params[:protocol].split("_")[0]
    list = params[:protocol].split("_")[1]

    render :update do |page|
      page.remove "protocol_#{protocol}"
      page.insert_html :bottom, list, render(:partial=>"protocol", :object => protocol)
      page.visual_effect :highlight, "protocol_#{protocol}"
    end

  end

def force_update
  msg = Message.new
  msg.msg = "y helo thar"

  client = DaemonClient.new
  client.send(msg)

  flash[:notice] = "Update Sent!"
  redirect_to :action => "index"
end

  private

  def init_chart(title, datasets)
    data = GoogleChartData.new :datasets => datasets
    axis = GoogleChartAxis.new :axis  => [GoogleChartAxis::LEFT, GoogleChartAxis::BOTTOM]
    chart = GoogleLineChart.new :chart_type => GoogleLineChart::XY , :width => 500, :height => 300, :title => title
    chart.data = data
    chart.axis = axis
    chart
  end

end
